// GAMEUI_H
#ifndef GAMEUI_H
#define GAMEUI_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QIcon>
#include <QSize>
#include <QStringList>
#include <QMessageBox>
#include <QDebug>
#include <QTextEdit>
#include <QLineEdit>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QGroupBox>
#include <QScrollBar>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class GameUI; }
QT_END_NAMESPACE

class GameUI : public QWidget
{
    Q_OBJECT

public:
    GameUI(QWidget *parent = nullptr);
    ~GameUI();

    //PUBLI UI METHODS (Controller Interface):
    void updateRequestedCards(const QStringList& cardNames);
    void updateSelectedCards(const QStringList& cardNames);
    void setTimerDisplay(int seconds);
    void enableGameControls(bool enabled);
    void resetGameUI();
    void markCardAsSelected(int index);
    void updateStopButtonAppearance(const QString& text, bool enabled);
    void updateGameStatus(const QString& status);
    void displayChatMessage(const QString& username, const QString& message);

signals:
    void cardSelected(int index, const QString& cardName);
    void selectedCardClicked(int index);
    void stopRequested();
    void resumeRequested();
    void exitRequested();
    void returnToMenu();

    void cardRequested(const QString& cardName);
    // the new signal for chat
    void chatMessageSent(const QString& message);

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

private:
    void setupUI();
    void connectSignals();

    void setRequestedCardImage(int index, const QString& cardName);
    void setSelectedCardImage(int index, const QString& cardName);
    QString getCardImagePath(const QString& cardName);
    bool isValidCardName(const QString& cardName);
    QPixmap loadCardImage(const QString& cardName);

    QPushButton* getRequestedCardButton(int index);
    QPushButton* getSelectedCardButton(int index);

    void clearRequestedCards();
    void clearSelectedCards();

//private:
    Ui::GameUI *ui;
    QStringList m_currentRequestedCards;
    QStringList m_currentSelectedCards;
    bool m_gameControlsEnabled;
    QLabel* statusLabel;

    // the new attribute for chat
    QTextEdit* m_chatDisplay;
    QLineEdit* m_chatInput;
    QPushButton* m_sendButton;
    QFrame* m_stickerPanel;
    QScrollArea* m_chatScrollArea;
    QStringList m_availableStickers;
    void setupChatUI();
    void setupStickerPanel();
    void addStickerToMessage(const QString& sticker);
    void sendChatMessage();
};

#endif // GAMEUI_H
