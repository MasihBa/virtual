#ifndef GAMEUI_H
#define GAMEUI_H

#include <QWidget>
#include <QStringList>
#include <QTimer>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <QPixmap>
#include <QIcon>
#include "sockethandler.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GameUI; }
QT_END_NAMESPACE

class GameUI : public QWidget
{
    Q_OBJECT
public:
    explicit GameUI(QWidget *parent = nullptr);
    ~GameUI();
    void setSocketHandler(SocketHandler* socketHandler);
    void updateRequestedCards(const QStringList& cardNames);
    void updateSelectedCards(const QStringList& cardNames);
    void setTimer(int seconds);
    void startTimer();
    void stopTimer();
    void enableGameControls(bool enabled);
    void resetGameState();

public slots:
    void onServerMessageReceived(const QJsonObject& message);

private slots:
    void onRequestedCard1Clicked();
    void onRequestedCard2Clicked();
    void onRequestedCard3Clicked();
    void onRequestedCard4Clicked();
    void onRequestedCard5Clicked();
    void onRequestedCard6Clicked();
    void onRequestedCard7Clicked();
    void onSelectedCard1Clicked();
    void onSelectedCard2Clicked();
    void onSelectedCard3Clicked();
    void onSelectedCard4Clicked();
    void onSelectedCard5Clicked();
    void onStopClicked();
    void onResumeClicked();
    void onExitClicked();
    void onTimerTick();

private:
    Ui::GameUI *ui;
    SocketHandler* m_socketHandler;
    QTimer* m_gameTimer;
    int m_remainingTime;
    QStringList m_currentRequestedCards;
    QStringList m_currentSelectedCards;
    bool m_gameControlsEnabled;
    void setupUI();
    void connectSignals();
    QString getCardImagePath(const QString& cardName);
    bool isValidCardName(const QString& cardName);
    QPixmap loadCardImage(const QString& cardName);
    void setRequestedCardImage(int index, const QString& cardName);
    void setSelectedCardImage(int index, const QString& cardName);
    void clearRequestedCards();
    void clearSelectedCards();
    void sendCardRequest(const QString& cardName);
    void sendGameAction(const QString& action);
    QPushButton* getRequestedCardButton(int index);
    QPushButton* getSelectedCardButton(int index);
signals:
    void cardRequested(const QString& cardName);
    void returnToMenu();
};

#endif // GAMEUI_H
