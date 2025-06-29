/********************************************************************************
** Form generated from reading UI file 'signin.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNIN_H
#define UI_SIGNIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SignIn
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QFormLayout *formLayout_4;
    QLabel *usernamelabel_signInPage;
    QLineEdit *usernameInSignInPagelineEdit;
    QWidget *layoutWidget_2;
    QFormLayout *formLayout_5;
    QLabel *passwordlabel_signInPage;
    QLineEdit *passInSignInPagelineEdit;
    QPushButton *signInpushButton_signInPage;
    QWidget *widget;
    QFormLayout *formLayout;
    QPushButton *passwordrecoverysigninpushButton;
    QLabel *passwordRecoverySigninlabel;
    QWidget *widget1;
    QFormLayout *formLayout_2;
    QPushButton *signupsigninpushButton;
    QLabel *signupsigninlabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SignIn)
    {
        if (SignIn->objectName().isEmpty())
            SignIn->setObjectName("SignIn");
        SignIn->resize(800, 600);
        centralwidget = new QWidget(SignIn);
        centralwidget->setObjectName("centralwidget");
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(230, 210, 301, 31));
        formLayout_4 = new QFormLayout(layoutWidget);
        formLayout_4->setObjectName("formLayout_4");
        formLayout_4->setContentsMargins(0, 0, 0, 0);
        usernamelabel_signInPage = new QLabel(layoutWidget);
        usernamelabel_signInPage->setObjectName("usernamelabel_signInPage");

        formLayout_4->setWidget(0, QFormLayout::ItemRole::LabelRole, usernamelabel_signInPage);

        usernameInSignInPagelineEdit = new QLineEdit(layoutWidget);
        usernameInSignInPagelineEdit->setObjectName("usernameInSignInPagelineEdit");

        formLayout_4->setWidget(0, QFormLayout::ItemRole::FieldRole, usernameInSignInPagelineEdit);

        layoutWidget_2 = new QWidget(centralwidget);
        layoutWidget_2->setObjectName("layoutWidget_2");
        layoutWidget_2->setGeometry(QRect(230, 240, 301, 31));
        formLayout_5 = new QFormLayout(layoutWidget_2);
        formLayout_5->setObjectName("formLayout_5");
        formLayout_5->setContentsMargins(0, 0, 0, 0);
        passwordlabel_signInPage = new QLabel(layoutWidget_2);
        passwordlabel_signInPage->setObjectName("passwordlabel_signInPage");

        formLayout_5->setWidget(0, QFormLayout::ItemRole::LabelRole, passwordlabel_signInPage);

        passInSignInPagelineEdit = new QLineEdit(layoutWidget_2);
        passInSignInPagelineEdit->setObjectName("passInSignInPagelineEdit");
        passInSignInPagelineEdit->setEchoMode(QLineEdit::EchoMode::Password);

        formLayout_5->setWidget(0, QFormLayout::ItemRole::FieldRole, passInSignInPagelineEdit);

        signInpushButton_signInPage = new QPushButton(centralwidget);
        signInpushButton_signInPage->setObjectName("signInpushButton_signInPage");
        signInpushButton_signInPage->setGeometry(QRect(450, 300, 83, 29));
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(230, 340, 400, 31));
        formLayout = new QFormLayout(widget);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        passwordrecoverysigninpushButton = new QPushButton(widget);
        passwordrecoverysigninpushButton->setObjectName("passwordrecoverysigninpushButton");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, passwordrecoverysigninpushButton);

        passwordRecoverySigninlabel = new QLabel(widget);
        passwordRecoverySigninlabel->setObjectName("passwordRecoverySigninlabel");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, passwordRecoverySigninlabel);

        widget1 = new QWidget(centralwidget);
        widget1->setObjectName("widget1");
        widget1->setGeometry(QRect(230, 370, 449, 31));
        formLayout_2 = new QFormLayout(widget1);
        formLayout_2->setObjectName("formLayout_2");
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        signupsigninpushButton = new QPushButton(widget1);
        signupsigninpushButton->setObjectName("signupsigninpushButton");

        formLayout_2->setWidget(0, QFormLayout::ItemRole::LabelRole, signupsigninpushButton);

        signupsigninlabel = new QLabel(widget1);
        signupsigninlabel->setObjectName("signupsigninlabel");

        formLayout_2->setWidget(0, QFormLayout::ItemRole::FieldRole, signupsigninlabel);

        SignIn->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SignIn);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        SignIn->setMenuBar(menubar);
        statusbar = new QStatusBar(SignIn);
        statusbar->setObjectName("statusbar");
        SignIn->setStatusBar(statusbar);

        retranslateUi(SignIn);

        QMetaObject::connectSlotsByName(SignIn);
    } // setupUi

    void retranslateUi(QMainWindow *SignIn)
    {
        SignIn->setWindowTitle(QCoreApplication::translate("SignIn", "MainWindow", nullptr));
        usernamelabel_signInPage->setText(QCoreApplication::translate("SignIn", "username", nullptr));
        usernameInSignInPagelineEdit->setPlaceholderText(QCoreApplication::translate("SignIn", "enter your username", nullptr));
        passwordlabel_signInPage->setText(QCoreApplication::translate("SignIn", "password", nullptr));
        passInSignInPagelineEdit->setPlaceholderText(QCoreApplication::translate("SignIn", "enter your password", nullptr));
        signInpushButton_signInPage->setText(QCoreApplication::translate("SignIn", "sign in", nullptr));
        passwordrecoverysigninpushButton->setText(QCoreApplication::translate("SignIn", "password recovery", nullptr));
        passwordRecoverySigninlabel->setText(QCoreApplication::translate("SignIn", "if you forget your password, clieck here", nullptr));
        signupsigninpushButton->setText(QCoreApplication::translate("SignIn", "           signup         ", nullptr));
        signupsigninlabel->setText(QCoreApplication::translate("SignIn", "if you don't have account, clieck here", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SignIn: public Ui_SignIn {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNIN_H
