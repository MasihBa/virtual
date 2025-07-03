#include "waiting.h"
#include "ui_waiting.h"
#include <QMessageBox>
#include <QDebug>

Waiting::Waiting(SocketHandler* socketHandler, const QString &username, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Waiting)
    , w_socketHandler(socketHandler)
    , w_username(username)
    , dotsCount(0)
    , m_gameUI(nullptr)
    , m_gameController(nullptr)
{
    ui->setupUi(this);

    setWindowTitle("Waiting for Players");
    setFixedSize(400, 300);

    disconnect(w_socketHandler, &SocketHandler::messageReceived, nullptr, nullptr);
    connect(w_socketHandler, &SocketHandler::messageReceived, this, &Waiting::onMessageReceived);
    connect(ui->cancelButton, &QPushButton::clicked, this, &Waiting::onCancelClicked);

    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &Waiting::updateWaitingText);
    animationTimer->start(500);

    ui->playersCountLabel->setText("Players: 1/4");

    qDebug() << "Sending join game request for:" << w_username;
    w_socketHandler->sendMessage(QString("6;%1").arg(w_username));///////////6;username
}

Waiting::~Waiting()
{
    if(animationTimer) {
        animationTimer->stop();
    }
    delete ui;
}

void Waiting::setGameComponents(GameUI* gameUI, GameUIController* gameController)
{
    m_gameUI = gameUI;
    m_gameController = gameController;
    qDebug() << "connecting gameUI and gameUIController to waiting page.";
}

void Waiting::startGame(const QString &gameData)
{
    if (m_gameController) {
        qDebug() << "start game with GameController";

        if (m_gameUI) {
            m_gameUI->show();
            qDebug() << "GameUI called.";
        }
        disconnect(w_socketHandler, &SocketHandler::messageReceived, nullptr, nullptr);
        connect(w_socketHandler, &SocketHandler::messageReceived, m_gameController, &GameUIController::onServerMessageReceived);

        m_gameController->startNewGame();
        qDebug() << "startNewGame called.";
        w_socketHandler->sendMessage(QString("20;0"));
        this->hide();

    } else {
        emit gameStarted(gameData);
        this->close();
    }
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

    if(parts[0] == "count") {
        if(parts.size() >= 2) {
            ui->playersCountLabel->setText(QString("Players: %1/4").arg(parts[1]));
        }
    }
    else if(parts[0] == "start" && parts[1] == "0") {
        qDebug() << "Game starting.";
        animationTimer->stop();
        startGame(msg);

    }
    else if(parts[0] == "-1") {
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
    w_socketHandler->sendMessage(QString("19;%1").arg(w_username));//////// 19;username -> cancel
    emit waitingCancelled();
    this->close();
}
