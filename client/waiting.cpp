#include<waiting.h>
#include "ui_waiting.h"
#include <QMessageBox>
#include <QDebug>

Waiting::Waiting(SocketHandler* socketHandler, const QString &username, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Waiting)
    , w_socketHandler(socketHandler)
    , w_username(username)
    , dotsCount(0)
{
    ui->setupUi(this);

    setWindowTitle("Waiting for Players");
    setFixedSize(400, 300);

    connect(w_socketHandler, &SocketHandler::messageReceived,this, &Waiting::onMessageReceived);

    connect(ui->cancelButton, &QPushButton::clicked,this, &Waiting::onCancelClicked);

    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout,this, &Waiting::updateWaitingText);
    animationTimer->start(500);

    ui->playersCountLabel->setText("Players: 1/4");

    qDebug() << "Sending join game request for:" << w_username;
    w_socketHandler->sendMessage(QString("3;%1").arg(w_username));
}

Waiting::~Waiting()
{
    if(animationTimer) {
        animationTimer->stop();
    }
    delete ui;
}

void Waiting::updateWaitingText()
{
    dotsCount = (dotsCount + 1) % 4;
    QString dots;
    for(int i = 0; i < dotsCount; i++) {
        dots += ".";
    }

    ui->waitingLabel->setText(QString("Waiting for players%1").arg(dots));
}

void Waiting::onMessageReceived(const QString &msg)
{
    qDebug() << "Waiting received message:" << msg;

    QStringList parts = msg.split(';');

    if(parts[0] == "waiting_players") {
        // Server sends: waiting_players;current_count;max_count
        if(parts.size() >= 3) {
            ui->playersCountLabel->setText(QString("Players:%1;%2").arg(parts[1], parts[2]));
        }
    }
    else if(parts[0] == "game_start") {
        qDebug() << "Game starting!";
        animationTimer->stop();
        emit gameStarted(msg);
        this->close();
    }
    else if(parts[0] == "join_failed") {
        QMessageBox::warning(this, "Failed", "Could not join game queue");
        emit waitingCancelled();
        this->close();
    }
}

void Waiting::onCancelClicked()
{
    qDebug() << "Cancel waiting for:" << w_username;
    if(animationTimer) {
        animationTimer->stop();
    }
    w_socketHandler->sendMessage(QString("4;%1").arg(w_username));
    emit waitingCancelled();
    this->close();
}
