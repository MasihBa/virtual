// #include "history.h"
// #include "ui_history.h"
// #include <QDebug>

// History::History(SocketHandler* socketHandler, const QString &username, QWidget* parent)
//     : QMainWindow(parent)
//     , ui(new Ui::History)
//     , h_socketHandler(socketHandler)
//     , h_username(username)
// {
//     ui->setupUi(this);
//     disconnect(h_socketHandler, &SocketHandler::messageReceived,nullptr, nullptr);
//     connect(h_socketHandler, &SocketHandler::messageReceived,this, &History::onMessageReceived);
//     disconnect(h_socketHandler, &SocketHandler::errorOccurred,nullptr, nullptr);
//     connect(h_socketHandler, &SocketHandler::errorOccurred,this, &History::onErrorOccurred);

//     connect(ui->closeButton, &QPushButton::clicked, this, &History::onCloseButtonClicked);
//     requestHistoryData();
// }

// History::~History()
// {
//     delete ui;
// }

// void History::requestHistoryData()
// {
//     qDebug() << "Requesting history data for user:" << h_username;
//     QString message = QString("6;%1\n").arg(h_username);
//     h_socketHandler->sendMessage(message);
// }

// void History::onMessageReceived(const QString& msg)
// {
//     qDebug() << "History received message:" << msg;

//     QString trimmedMsg = msg.trimmed();
// }

// void History::onErrorOccurred(const QString& err)
// {
//     qDebug() << "History socket error:" << err;
// }

// void History::onCloseButtonClicked()
// {
//     qDebug() << "Close button clicked";
//     emit historyClosed();
//     this->close();
// }

#include "history.h"
#include "ui_history.h"
#include <QDebug>
#include <QStringList>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QLabel>

History::History(SocketHandler* socketHandler, const QString &username, QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::History)
    , h_socketHandler(socketHandler)
    , h_username(username)
{
    ui->setupUi(this);

    disconnect(h_socketHandler, &SocketHandler::messageReceived, nullptr, nullptr);
    connect(h_socketHandler, &SocketHandler::messageReceived, this, &History::onMessageReceived);
    disconnect(h_socketHandler, &SocketHandler::errorOccurred, nullptr, nullptr);
    connect(h_socketHandler, &SocketHandler::errorOccurred, this, &History::onErrorOccurred);
    connect(ui->closeButton, &QPushButton::clicked, this, &History::onCloseButtonClicked);
    requestHistoryData();
}

History::~History()
{
    delete ui;
}

void History::requestHistoryData()
{
    qDebug() << "Requesting history data for user:" << h_username;
    QString message = QString("6;%1\n").arg(h_username);
    h_socketHandler->sendMessage(message);
}

void History::onMessageReceived(const QString& msg)
{
    qDebug() << "History received message:" << msg;

    QString trimmedMsg = msg.trimmed();

    if (trimmedMsg.startsWith("history;")) {
        processHistoryData(trimmedMsg);
        emit historyDataReceived(trimmedMsg);
    }
}

void History::processHistoryData(const QString& historyData)
{
    // history;numberofmaches;username1;username2;username3;username4;winner1;winner2;winner3;date
    QStringList parts = historyData.split(';');

    if (parts.size() < 2) {
        qDebug() << "Invalid history data format";
        return;
    }

    if (parts[0] != "history") {
        qDebug() << "Not a history message";
        return;
    }

    int numberOfMatches = parts[1].toInt();
    qDebug() << "Number of matches:" << numberOfMatches;

    ui->historyTable->clear();
    ui->historyTable->setRowCount(numberOfMatches);
    ui->historyTable->setColumnCount(7); // Players, Set1 Winner, Set2 Winner, Set3 Winner, Date

    QStringList headers;
    headers << "Players" << "Set 1 Winner" << "Set 2 Winner" << "Set 3 Winner" << "Date";
    ui->historyTable->setHorizontalHeaderLabels(headers);

    int dataIndex = 2;

    for (int match = 0; match < numberOfMatches; match++) {
        if (dataIndex + 7 >= parts.size()) {
            qDebug() << "Insufficient data for match" << match;
            break;
        }
        QString player1 = parts[dataIndex++];
        QString player2 = parts[dataIndex++];
        QString player3 = parts[dataIndex++];
        QString player4 = parts[dataIndex++];
        QString winner1 = parts[dataIndex++];
        QString winner2 = parts[dataIndex++];
        QString winner3 = parts[dataIndex++];
        QString matchDate = parts[dataIndex++];
        QString playersStr = QString("%1, %2, %3, %4").arg(player1, player2, player3, player4);
        ui->historyTable->setItem(match, 0, new QTableWidgetItem(playersStr));
        ui->historyTable->setItem(match, 1, new QTableWidgetItem(winner1));
        ui->historyTable->setItem(match, 2, new QTableWidgetItem(winner2));
        ui->historyTable->setItem(match, 3, new QTableWidgetItem(winner3));
        ui->historyTable->setItem(match, 4, new QTableWidgetItem(matchDate));

        qDebug() << "Match" << match << ":" << playersStr << "| Winners:" << winner1 << winner2 << winner3 << "| Date:" << matchDate;
    }

    ui->historyTable->resizeColumnsToContents();
    ui->historyTable->horizontalHeader()->setStretchLastSection(true);
}

void History::onErrorOccurred(const QString& err)
{
    qDebug() << "History socket error:" << err;
    if (ui->historyTable) {
        ui->historyTable->clear();
        ui->historyTable->setRowCount(1);
        ui->historyTable->setColumnCount(1);
        ui->historyTable->setItem(0, 0, new QTableWidgetItem("Error loading history: " + err));
    }
}

void History::onCloseButtonClicked()
{
    qDebug() << "Close button clicked";
    emit historyClosed();
    this->close();
}
