#include "menu.h"
#include "ui_menu.h"
#include <QDebug>
#include<changeInfo.h>
#include<QMessageBox.h>

Menu::Menu(SocketHandler* socketHandler, const QString &_username, QWidget *parent)
    :QWidget(parent)
    ,ui(new Ui::Menu)
    ,signUpPage(nullptr)
    ,m_socketHandler(socketHandler)
    ,changeInfoPage(nullptr)
    ,m_username(_username)
    ,historyPage(nullptr)
    ,waitingPage(nullptr)

{
    ui->setupUi(this);
    connect(ui->startGameButton, &QPushButton::clicked, this, &Menu::handleStartGame);
    connect(ui->historyButton, &QPushButton::clicked, this, &Menu::handleHistory);
    connect(ui->changeInfoButton, &QPushButton::clicked, this, &Menu::handleChangeInfo);
    connect(ui->logOutButton, &QPushButton::clicked, this, &Menu::handleLogOut);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::handleStartGame()
{
    qDebug() << "Starting game for user:" << m_username;

    GameUI* gameUI = new GameUI();
    GameUIController* gameController = new GameUIController(gameUI, m_socketHandler, m_username);

    waitingPage = new Waiting(m_socketHandler, m_username, nullptr);
    waitingPage->setGameComponents(gameUI, gameController);
    connect(waitingPage, &Waiting::gameStarted, this, &Menu::onGameStarted);
    connect(waitingPage, &Waiting::waitingCancelled, this, &Menu::onWaitingCancelled);
    connect(gameController, &GameUIController::returnToMenu, this, [this]() {
        this->show();
    });
    this->hide();
    disconnect(m_socketHandler, &SocketHandler::messageReceived, nullptr, nullptr);
    connect(m_socketHandler, &SocketHandler::messageReceived, waitingPage, &Waiting::onMessageReceived);
    waitingPage->show();//////////////////////////////////////////////////////////////////////////////////////////////
}

void Menu::onGameStarted(const QString &gameData)
{
    qDebug() << "Game started with data:" << gameData;
    QMessageBox::information(this, "Game Started", "Game is starting! (Game class will be implemented later)");

    this->show();

    // Game *gamePage = new Game(m_socketHandler, m_username, gameData);
    // gamePage->show();
    // this->hide();
}

void Menu::onWaitingCancelled()
{
    qDebug() << "Waiting cancelled, returning to menu";
    this->show();
}

void Menu::handleHistory()
{
    if (!historyPage) {
        historyPage = new History(m_socketHandler, m_username, this);

        connect(historyPage, &History::historyDataReceived,
                this, &Menu::onHistoryDataReceived);

        connect(historyPage, &History::historyClosed,
                this, &Menu::onHistoryClosed);
    }

    historyPage->show();
    historyPage->raise();
    historyPage->activateWindow();
}

void Menu::onHistoryDataReceived(const QString &data)
{
    qDebug() << "History data received:" << data;

    if (!data.isEmpty()) {
        QStringList historyItems = data.split(";");

        qDebug() << "History items count:" << historyItems.size();
        for (int i = 0; i < historyItems.size(); ++i) {
            qDebug() << "Item" << i << ":" << historyItems[i];
        }

       /// I should proper user in history.ui.....................
    }
}

void Menu::onHistoryClosed()
{
    qDebug() << "History window closed";
}

void Menu::handleChangeInfo()
{
    if (!changeInfoPage) {
        changeInfoPage = new ChangeInfo(m_socketHandler, m_username, this);
        connect(changeInfoPage, &ChangeInfo::infoChanged,
                this, &Menu::onInfoChanged);
        connect(changeInfoPage, &ChangeInfo::changeCancelled,
                this, &Menu::onInfoCancelled);
    }
    disconnect(m_socketHandler, &SocketHandler::messageReceived,nullptr, nullptr);
    connect(m_socketHandler, &SocketHandler::messageReceived,
            changeInfoPage, &ChangeInfo::onMessageReceived);
    disconnect(m_socketHandler, &SocketHandler::errorOccurred,nullptr, nullptr);
    connect(m_socketHandler, &SocketHandler::errorOccurred,
            changeInfoPage, &ChangeInfo::onErrorOccurred);
    changeInfoPage->show();
    changeInfoPage->raise();
    changeInfoPage->activateWindow();
}

void Menu::handleLogOut()
{
    qDebug() << "User requested logout";
    emit logOutRequested();
    this->close();
}

void Menu::onInfoChanged()
{
    qDebug() << "User info changed successfully";

}

void Menu::onInfoCancelled()
{
    qDebug() << "Change info cancelled by user";
}

void Menu::onStartGameClicked()
{
    emit gameStartRequested();
}
