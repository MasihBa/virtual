// WAITING_H
#ifndef WAITING_H
#define WAITING_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include "sockethandler.h"
#include "gameui.h"
#include "gameuicontroller.h"

namespace Ui {
class Waiting;
}

class Waiting : public QWidget
{
    Q_OBJECT

public:
    explicit Waiting(SocketHandler* socketHandler, const QString &username, QWidget *parent = nullptr);
    ~Waiting();
    void setGameComponents(GameUI* gameUI, GameUIController* gameController);
signals:
    void gameStarted(const QString &gameData);
    void waitingCancelled();

public slots:
    void onMessageReceived(const QString &msg);
    void updateWaitingText();
    void onCancelClicked();

private:
    Ui::Waiting *ui;
    SocketHandler* w_socketHandler;
    QString w_username;
    QTimer *animationTimer;
    int dotsCount;
    GameUI* m_gameUI;
    GameUIController* m_gameController;
    void startGame(const QString &gameData);
};

#endif // WAITING_H
