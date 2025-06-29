/********************************************************************************
** Form generated from reading UI file 'signup.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUP_H
#define UI_SIGNUP_H

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

class Ui_SignUp
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QFormLayout *formLayout_18;
    QLabel *emailLabel_4;
    QLineEdit *emailLineEdit_2;
    QWidget *layoutWidget_4;
    QFormLayout *formLayout_17;
    QLabel *firstnameLabel_2;
    QLineEdit *firstnameLineEdit_2;
    QWidget *layoutWidget_6;
    QFormLayout *formLayout_14;
    QLabel *lastnameLabel_2;
    QLineEdit *lastnameLineEdit_2;
    QWidget *layoutWidget_5;
    QFormLayout *formLayout_15;
    QLabel *emailLabel_3;
    QLineEdit *phonenumberLineEdit_2;
    QWidget *layoutWidget_3;
    QFormLayout *formLayout_13;
    QLineEdit *passwordLineEdit_2;
    QLabel *passwordLabel_2;
    QPushButton *signupPushButton;
    QWidget *layoutWidget_2;
    QFormLayout *formLayout_16;
    QLabel *usernameLabel_2;
    QLineEdit *usernameLineEdit_2;
    QLabel *labelErrorMessage;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SignUp)
    {
        if (SignUp->objectName().isEmpty())
            SignUp->setObjectName("SignUp");
        SignUp->resize(800, 600);
        centralwidget = new QWidget(SignUp);
        centralwidget->setObjectName("centralwidget");
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(230, 250, 331, 31));
        formLayout_18 = new QFormLayout(layoutWidget);
        formLayout_18->setObjectName("formLayout_18");
        formLayout_18->setContentsMargins(0, 0, 0, 0);
        emailLabel_4 = new QLabel(layoutWidget);
        emailLabel_4->setObjectName("emailLabel_4");

        formLayout_18->setWidget(0, QFormLayout::ItemRole::LabelRole, emailLabel_4);

        emailLineEdit_2 = new QLineEdit(layoutWidget);
        emailLineEdit_2->setObjectName("emailLineEdit_2");

        formLayout_18->setWidget(0, QFormLayout::ItemRole::FieldRole, emailLineEdit_2);

        layoutWidget_4 = new QWidget(centralwidget);
        layoutWidget_4->setObjectName("layoutWidget_4");
        layoutWidget_4->setGeometry(QRect(230, 130, 331, 31));
        formLayout_17 = new QFormLayout(layoutWidget_4);
        formLayout_17->setObjectName("formLayout_17");
        formLayout_17->setContentsMargins(0, 0, 0, 0);
        firstnameLabel_2 = new QLabel(layoutWidget_4);
        firstnameLabel_2->setObjectName("firstnameLabel_2");

        formLayout_17->setWidget(0, QFormLayout::ItemRole::LabelRole, firstnameLabel_2);

        firstnameLineEdit_2 = new QLineEdit(layoutWidget_4);
        firstnameLineEdit_2->setObjectName("firstnameLineEdit_2");

        formLayout_17->setWidget(0, QFormLayout::ItemRole::FieldRole, firstnameLineEdit_2);

        layoutWidget_6 = new QWidget(centralwidget);
        layoutWidget_6->setObjectName("layoutWidget_6");
        layoutWidget_6->setGeometry(QRect(230, 160, 331, 31));
        formLayout_14 = new QFormLayout(layoutWidget_6);
        formLayout_14->setObjectName("formLayout_14");
        formLayout_14->setContentsMargins(0, 0, 0, 0);
        lastnameLabel_2 = new QLabel(layoutWidget_6);
        lastnameLabel_2->setObjectName("lastnameLabel_2");

        formLayout_14->setWidget(0, QFormLayout::ItemRole::LabelRole, lastnameLabel_2);

        lastnameLineEdit_2 = new QLineEdit(layoutWidget_6);
        lastnameLineEdit_2->setObjectName("lastnameLineEdit_2");

        formLayout_14->setWidget(0, QFormLayout::ItemRole::FieldRole, lastnameLineEdit_2);

        layoutWidget_5 = new QWidget(centralwidget);
        layoutWidget_5->setObjectName("layoutWidget_5");
        layoutWidget_5->setGeometry(QRect(230, 280, 331, 30));
        formLayout_15 = new QFormLayout(layoutWidget_5);
        formLayout_15->setObjectName("formLayout_15");
        formLayout_15->setContentsMargins(0, 0, 0, 0);
        emailLabel_3 = new QLabel(layoutWidget_5);
        emailLabel_3->setObjectName("emailLabel_3");

        formLayout_15->setWidget(0, QFormLayout::ItemRole::LabelRole, emailLabel_3);

        phonenumberLineEdit_2 = new QLineEdit(layoutWidget_5);
        phonenumberLineEdit_2->setObjectName("phonenumberLineEdit_2");

        formLayout_15->setWidget(0, QFormLayout::ItemRole::FieldRole, phonenumberLineEdit_2);

        layoutWidget_3 = new QWidget(centralwidget);
        layoutWidget_3->setObjectName("layoutWidget_3");
        layoutWidget_3->setGeometry(QRect(230, 220, 331, 31));
        formLayout_13 = new QFormLayout(layoutWidget_3);
        formLayout_13->setObjectName("formLayout_13");
        formLayout_13->setContentsMargins(0, 0, 0, 0);
        passwordLineEdit_2 = new QLineEdit(layoutWidget_3);
        passwordLineEdit_2->setObjectName("passwordLineEdit_2");
        passwordLineEdit_2->setEchoMode(QLineEdit::EchoMode::Password);

        formLayout_13->setWidget(0, QFormLayout::ItemRole::FieldRole, passwordLineEdit_2);

        passwordLabel_2 = new QLabel(layoutWidget_3);
        passwordLabel_2->setObjectName("passwordLabel_2");

        formLayout_13->setWidget(0, QFormLayout::ItemRole::LabelRole, passwordLabel_2);

        signupPushButton = new QPushButton(centralwidget);
        signupPushButton->setObjectName("signupPushButton");
        signupPushButton->setGeometry(QRect(480, 400, 83, 29));
        layoutWidget_2 = new QWidget(centralwidget);
        layoutWidget_2->setObjectName("layoutWidget_2");
        layoutWidget_2->setGeometry(QRect(230, 190, 331, 31));
        formLayout_16 = new QFormLayout(layoutWidget_2);
        formLayout_16->setObjectName("formLayout_16");
        formLayout_16->setContentsMargins(0, 0, 0, 0);
        usernameLabel_2 = new QLabel(layoutWidget_2);
        usernameLabel_2->setObjectName("usernameLabel_2");

        formLayout_16->setWidget(0, QFormLayout::ItemRole::LabelRole, usernameLabel_2);

        usernameLineEdit_2 = new QLineEdit(layoutWidget_2);
        usernameLineEdit_2->setObjectName("usernameLineEdit_2");

        formLayout_16->setWidget(0, QFormLayout::ItemRole::FieldRole, usernameLineEdit_2);

        labelErrorMessage = new QLabel(centralwidget);
        labelErrorMessage->setObjectName("labelErrorMessage");
        labelErrorMessage->setGeometry(QRect(200, 420, 161, 91));
        SignUp->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SignUp);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        SignUp->setMenuBar(menubar);
        statusbar = new QStatusBar(SignUp);
        statusbar->setObjectName("statusbar");
        SignUp->setStatusBar(statusbar);

        retranslateUi(SignUp);

        QMetaObject::connectSlotsByName(SignUp);
    } // setupUi

    void retranslateUi(QMainWindow *SignUp)
    {
        SignUp->setWindowTitle(QCoreApplication::translate("SignUp", "MainWindow", nullptr));
        emailLabel_4->setText(QCoreApplication::translate("SignUp", "email       ", nullptr));
        emailLineEdit_2->setPlaceholderText(QCoreApplication::translate("SignUp", "email must contain @gmail.com", nullptr));
        firstnameLabel_2->setText(QCoreApplication::translate("SignUp", "first name", nullptr));
        firstnameLineEdit_2->setPlaceholderText(QCoreApplication::translate("SignUp", "firstname must contain a_z", nullptr));
        lastnameLabel_2->setText(QCoreApplication::translate("SignUp", "last name", nullptr));
        lastnameLineEdit_2->setPlaceholderText(QCoreApplication::translate("SignUp", "lastname must contain a_z", nullptr));
        emailLabel_3->setText(QCoreApplication::translate("SignUp", "phone number", nullptr));
        phonenumberLineEdit_2->setPlaceholderText(QCoreApplication::translate("SignUp", "example: 989131234567", nullptr));
        passwordLineEdit_2->setPlaceholderText(QCoreApplication::translate("SignUp", "password must contain a_z or 0_9", nullptr));
        passwordLabel_2->setText(QCoreApplication::translate("SignUp", "password", nullptr));
        signupPushButton->setText(QCoreApplication::translate("SignUp", "signup", nullptr));
        usernameLabel_2->setText(QCoreApplication::translate("SignUp", "username", nullptr));
        usernameLineEdit_2->setPlaceholderText(QCoreApplication::translate("SignUp", "username must contain a_z or 0_9", nullptr));
        labelErrorMessage->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SignUp: public Ui_SignUp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUP_H
