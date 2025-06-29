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
    connect(m_socketHandler, &SocketHandler::connected,
            this, &MainWindow::onConnected);
    connect(m_socketHandler, &SocketHandler::errorOccurred,
            this, [this](const QString &err) {
                QMessageBox::critical(this, "Connection Error", err);
            });
    m_socketHandler->connectToServer();
}

void MainWindow::onConnected()
{
    qDebug() << "Connected to server.";
    showSignInPage();
}

void MainWindow::showSignInPage()
{
    if (!signInPage) {
        signInPage = new SignIn(m_socketHandler);
        connect(signInPage, &SignIn::requestSignUpPage,
                this, &MainWindow::showSignUpPage);
        connect(signInPage, &SignIn::requestPasswordRecoveryPage,
                this, &MainWindow::showFindPasswordPage);
        connect(signInPage, &SignIn::signInSuccess,
                this, &MainWindow::showMenuPage);
    }
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
    }
    menuPage->show();
    signInPage->hide();
    if (signUpPage) signUpPage->hide();
    if (findPasswordPage) findPasswordPage->hide();
}

void MainWindow::onLogOutRequested()
{
    qDebug() << "Handling logout - returning to signin";

    currentUsername.clear();

    if (menuPage) {
        delete menuPage;
        menuPage = nullptr;
    }

    showSignInPage();
}


