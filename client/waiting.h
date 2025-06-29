#ifndef WAITING_H
#define WAITING_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include "sockethandler.h"

namespace Ui {
class Waiting;
}

class Waiting : public QWidget
{
    Q_OBJECT

public:
    explicit Waiting(SocketHandler* socketHandler, const QString &username, QWidget *parent = nullptr);
    ~Waiting();

signals:
    void gameStarted(const QString &gameData);
    void waitingCancelled();

private slots:
    void onMessageReceived(const QString &msg);
    void updateWaitingText();
    void onCancelClicked();

private:
    Ui::Waiting *ui;
    SocketHandler* w_socketHandler;
    QString w_username;
    QTimer *animationTimer;
    int dotsCount;
};

#endif // WAITING_H
