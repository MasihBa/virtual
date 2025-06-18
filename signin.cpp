#include <signin.h>
#include <ui_signin.h>

SignIn::SignIn(const QString& enteredPassByUser,const QString& enteredUsernameByUser, QWidget* parent):enteredPass(enteredPassByUser), enteredUsername(enteredUsername), QMainWindow(parent), ui(new Ui::SignIn){
    ui->setupUi(this);
    connect(ui->signInpushButton_signInPage, &QPushButton::clicked, this, &SignIn::onSignInClicked);
}

// this method(validatePassword()) should be implemented in server project
bool SignIn::validatePassword(){}

// this method(validateUsername()) should be implemented in server project
bool SignIn::validateUsername(){}

SignIn::~SignIn(){
    delete ui;
}

void SignIn::onSignInClicked(){
    QString enteryusername = ui->usernameInSignInPagelineEdit->text();
    QString enterypassword = ui->passInSignInPagelineEdit->text();
}
