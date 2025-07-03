// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked,
            this, &MainWindow::onConnectClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onConnectClicked()
{
    QString ip = ui->iplineEdit->text().trimmed();
    if (ip.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter server IP.");
        return;
    }

    m_socketHandler = new SocketHandler(ip, 10200, this);
    disconnect(m_socketHandler, &SocketHandler::connected, nullptr, nullptr);
    connect(m_socketHandler, &SocketHandler::connected,this, &MainWindow::onConnected);
    disconnect(m_socketHandler, &SocketHandler::errorOccurred, nullptr, nullptr);
    connect(m_socketHandler, &SocketHandler::errorOccurred,this, [this](const QString &err) {
                QMessageBox::critical(this, "Connection Error", err);
            });
    m_socketHandler->connectToServer();
}

void MainWindow::onConnected()
{
    qDebug() << "Connected to server.";
    // the new change to hide mainwindow when the the signin page is opened
    this->hide();
    showSignInPage();
}

void MainWindow::showSignInPage()
{
    if (!signInPage) {
        signInPage = new SignIn(m_socketHandler);
        connect(signInPage, &SignIn::requestSignUpPage,this, &MainWindow::showSignUpPage);
        connect(signInPage, &SignIn::requestPasswordRecoveryPage,this, &MainWindow::showFindPasswordPage);
        connect(signInPage, &SignIn::signInSuccess,this, &MainWindow::showMenuPage);
    }
    disconnect(m_socketHandler, &SocketHandler::messageReceived, nullptr, nullptr);
    connect(m_socketHandler, &SocketHandler::messageReceived,
            signInPage, &SignIn::onMessageReceived);
    disconnect(m_socketHandler, &SocketHandler::connected, nullptr, nullptr);
    connect(m_socketHandler, &SocketHandler::connected,
            signInPage, &SignIn::onConnected);
    disconnect(m_socketHandler, &SocketHandler::errorOccurred, nullptr, nullptr);
    connect(m_socketHandler, &SocketHandler::errorOccurred,
            signInPage, &SignIn::onErrorOccurred);
    signInPage->show();
    if (signUpPage) signUpPage->hide();
    if (findPasswordPage) findPasswordPage->hide();
    if (menuPage) menuPage->hide();
}

void MainWindow::showSignUpPage()
{
    if (!signUpPage) {
        signUpPage = new SignUp(m_socketHandler);
        connect(signUpPage, &SignUp::signupCompleted,
                this, &MainWindow::showSignInPage);
    }
    // connect(ui->signupPushButton, &QPushButton::clicked,signUpPage, &SignUp::onSignupClicked);
    disconnect(m_socketHandler, &SocketHandler::connected, nullptr, nullptr);
    connect(m_socketHandler, &SocketHandler::connected,signUpPage, &SignUp::onConnected);
    disconnect(m_socketHandler, &SocketHandler::messageReceived, nullptr, nullptr);
    connect(m_socketHandler, &SocketHandler::messageReceived,signUpPage, &SignUp::onMessageReceived);
    disconnect(m_socketHandler, &SocketHandler::errorOccurred, nullptr, nullptr);
    connect(m_socketHandler, &SocketHandler::errorOccurred,signUpPage, &SignUp::onErrorOccurred);
    disconnect(m_socketHandler, &SocketHandler::disconnected, nullptr, nullptr);
    connect(m_socketHandler, &SocketHandler::disconnected,signUpPage, &SignUp::onDisconnected);
    signUpPage->show();
    signInPage->hide();
    if (findPasswordPage) findPasswordPage->hide();
    if (menuPage) menuPage->hide();
}

void MainWindow::showFindPasswordPage()
{
    if (!findPasswordPage) {
        findPasswordPage = new FindPassword(m_socketHandler);
        connect(findPasswordPage, &FindPassword::recoveryCompleted,
                this, &MainWindow::showSignInPage);
    }
    disconnect(m_socketHandler, &SocketHandler::messageReceived,nullptr, nullptr);
    connect(m_socketHandler, &SocketHandler::messageReceived,
            findPasswordPage, &FindPassword::onMessageReceived);
    disconnect(m_socketHandler, &SocketHandler::errorOccurred,nullptr, nullptr);
    connect(m_socketHandler, &SocketHandler::errorOccurred,
            findPasswordPage, &FindPassword::onErrorOccurred);
    findPasswordPage->show();
    signInPage->hide();
    if (signUpPage) signUpPage->hide();
    if (menuPage) menuPage->hide();
}

void MainWindow::showMenuPage(const QString &_username)
{
    currentUsername = _username;

    if (!menuPage) {
        menuPage = new Menu(m_socketHandler, _username);
        connect(menuPage, &Menu::logOutRequested,
                this, &MainWindow::onLogOutRequested);
        connect(menuPage, &Menu::gameStartRequested,
                this, &MainWindow::onGameStartRequested);
    }
    menuPage->show();
    signInPage->hide();
    if (signUpPage) signUpPage->hide();
    if (findPasswordPage) findPasswordPage->hide();
}

// void MainWindow::onLogOutRequested()
// {
//     qDebug() << "Handling logout-returning to signin";
//     currentUsername.clear();
//     if (menuPage) {
//         delete menuPage;
//         menuPage = nullptr;
//     }
//     showSignInPage();
// }
// new added for start game option
void MainWindow::onGameStartRequested()
{
    qDebug() << "Starting game for user:" << currentUsername;

    if (!gameUI) {
        gameUI = new GameUI(this);
    }

    if (!gameUIController) {
        gameUIController = new GameUIController(gameUI, m_socketHandler, currentUsername, this);

        connect(gameUIController, &GameUIController::returnToMenu,
                this, &MainWindow::onReturnToMenuFromGame);
        connect(gameUIController, &GameUIController::gameError,
                this, &MainWindow::onGameError);
    }
    if (menuPage) menuPage->hide();
    gameUI->show();
    gameUIController->startNewGame();
}

void MainWindow::onReturnToMenuFromGame()
{
    qDebug() << "Returning to menu from game";

    if (gameUI) {
        gameUI->hide();
    }

    if (menuPage) {
        menuPage->show();
    }
}

void MainWindow::onGameError(const QString& error)
{
    qWarning() << "Game error:" << error;

    QMessageBox::critical(this, "Game Error",
                         QString("Game error occurred:%1").arg(error));

    onReturnToMenuFromGame();
}

void MainWindow::onLogOutRequested()
{
    qDebug() << "Handling logout-returning to signin";
    currentUsername.clear();

    if (gameUIController) {
        delete gameUIController;
        gameUIController = nullptr;
    }

    if (gameUI) {
        delete gameUI;
        gameUI = nullptr;
    }

    if (menuPage) {
        delete menuPage;
        menuPage = nullptr;
    }

    showSignInPage();
}

