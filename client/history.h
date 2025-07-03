// #ifndef HISTORY_H
// #define HISTORY_H

// #include <QMainWindow>
// #include <QWidget>
// #include <QString>
// #include "sockethandler.h"

// QT_BEGIN_NAMESPACE
// namespace Ui { class History; }
// QT_END_NAMESPACE

// class History : public QMainWindow
// {
//     Q_OBJECT

// public:
//     explicit History(SocketHandler* socketHandler, const QString &username, QWidget* parent = nullptr);
//     ~History() override;

// signals:
//     void historyDataReceived(const QString &data);
//     void historyClosed();

// private slots:
//     void onMessageReceived(const QString& msg);
//     void onErrorOccurred(const QString& err);
//     void onCloseButtonClicked();

// private:
//     Ui::History *ui;
//     SocketHandler *h_socketHandler;
//     QString h_username;

//     void requestHistoryData();
// };

// #endif // HISTORY_H

#ifndef HISTORY_H
#define HISTORY_H

#include <QMainWindow>
#include <QWidget>
#include <QString>
#include "sockethandler.h"

QT_BEGIN_NAMESPACE
namespace Ui { class History; }
QT_END_NAMESPACE

class History : public QMainWindow
{
    Q_OBJECT

public:
    explicit History(SocketHandler* socketHandler, const QString &username, QWidget* parent = nullptr);
    ~History() override;

signals:
    void historyDataReceived(const QString &data);
    void historyClosed();

private slots:
    void onMessageReceived(const QString& msg);
    void onErrorOccurred(const QString& err);
    void onCloseButtonClicked();

private:
    Ui::History *ui;
    SocketHandler *h_socketHandler;
    QString h_username;

    void requestHistoryData();
    void processHistoryData(const QString& historyData);
};

#endif // HISTORY_H
