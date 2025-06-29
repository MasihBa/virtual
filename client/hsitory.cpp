// #include "history.h"
// #include "ui_history.h"
// #include <QMessageBox>
// #include <QDebug>

// History::History(SocketHandler* socketHandler, const QString &username, QWidget* parent)
//     : QMainWindow(parent)
//     , ui(new Ui::History)
//     , h_socketHandler(socketHandler)
//     , h_username(username)
// {
//     ui->setupUi(this);

//     connect(ui->closeButton, &QPushButton::clicked,
//             this, &History::onCloseButtonClicked);

//     if (h_socketHandler) {
//         connect(h_socketHandler, &SocketHandler::messageReceived,
//                 this, &History::onMessageReceived);
//         connect(h_socketHandler, &SocketHandler::errorOccurred,
//                 this, &History::onErrorOccurred);

//         requestHistoryData();
//     } else {
//         QMessageBox::critical(this, "Internal Error", "SocketHandler is null");
//     }
// }

// void History::requestHistoryData()
// {
//     QString msg = QString("6;%1").arg(h_username);
//     qDebug() << "Requesting history data:" << msg;
//     h_socketHandler->sendMessage(msg);
// }

// void History::onMessageReceived(const QString& msg)
// {
//     qDebug() << "Server reply history:" << msg;

//     emit historyDataReceived(msg.trimmed());

//     // processHistoryData(msg.trimmed());
// }


// void History::onErrorOccurred(const QString& err)
// {
//     qDebug() << "History network error:" << err;
//     QMessageBox::critical(this, "Network Error", err);
// }

// void History::onCloseButtonClicked()
// {
//     emit historyClosed();
//     this->close();
// }
#include "history.h"
#include "ui_history.h"
#include <QDebug>

History::History(SocketHandler* socketHandler, const QString &username, QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::History)
    , h_socketHandler(socketHandler)
    , h_username(username)
{
    ui->setupUi(this);

    connect(h_socketHandler, &SocketHandler::messageReceived,
            this, &History::onMessageReceived);
    connect(h_socketHandler, &SocketHandler::errorOccurred,
            this, &History::onErrorOccurred);

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

}

void History::onErrorOccurred(const QString& err)
{
    qDebug() << "History socket error:" << err;
}

void History::onCloseButtonClicked()
{
    qDebug() << "Close button clicked";
    emit historyClosed();
    this->close();
}
