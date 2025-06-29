/********************************************************************************
** Form generated from reading UI file 'findpassword.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDPASSWORD_H
#define UI_FINDPASSWORD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FindPassword
{
public:
    QWidget *centralwidget;
    QPushButton *passwordRecoverypushButton;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *passwordRecoveryUsernamelabel;
    QLineEdit *passwordRecoveryUsernamelineEdit;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *passwordRecoveryPhoneNumberlabel;
    QLineEdit *passwordRecoveryPhoneNumberlineEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *FindPassword)
    {
        if (FindPassword->objectName().isEmpty())
            FindPassword->setObjectName("FindPassword");
        FindPassword->resize(800, 600);
        centralwidget = new QWidget(FindPassword);
        centralwidget->setObjectName("centralwidget");
        passwordRecoverypushButton = new QPushButton(centralwidget);
        passwordRecoverypushButton->setObjectName("passwordRecoverypushButton");
        passwordRecoverypushButton->setGeometry(QRect(390, 370, 141, 31));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(passwordRecoverypushButton->sizePolicy().hasHeightForWidth());
        passwordRecoverypushButton->setSizePolicy(sizePolicy);
        layoutWidget_2 = new QWidget(centralwidget);
        layoutWidget_2->setObjectName("layoutWidget_2");
        layoutWidget_2->setGeometry(QRect(180, 250, 361, 30));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        passwordRecoveryUsernamelabel = new QLabel(layoutWidget_2);
        passwordRecoveryUsernamelabel->setObjectName("passwordRecoveryUsernamelabel");

        horizontalLayout_2->addWidget(passwordRecoveryUsernamelabel);

        passwordRecoveryUsernamelineEdit = new QLineEdit(layoutWidget_2);
        passwordRecoveryUsernamelineEdit->setObjectName("passwordRecoveryUsernamelineEdit");
        sizePolicy.setHeightForWidth(passwordRecoveryUsernamelineEdit->sizePolicy().hasHeightForWidth());
        passwordRecoveryUsernamelineEdit->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(passwordRecoveryUsernamelineEdit);

        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(180, 180, 361, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        passwordRecoveryPhoneNumberlabel = new QLabel(layoutWidget);
        passwordRecoveryPhoneNumberlabel->setObjectName("passwordRecoveryPhoneNumberlabel");

        horizontalLayout->addWidget(passwordRecoveryPhoneNumberlabel);

        passwordRecoveryPhoneNumberlineEdit = new QLineEdit(layoutWidget);
        passwordRecoveryPhoneNumberlineEdit->setObjectName("passwordRecoveryPhoneNumberlineEdit");
        passwordRecoveryPhoneNumberlineEdit->setEnabled(true);

        horizontalLayout->addWidget(passwordRecoveryPhoneNumberlineEdit);

        FindPassword->setCentralWidget(centralwidget);
        menubar = new QMenuBar(FindPassword);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        FindPassword->setMenuBar(menubar);
        statusbar = new QStatusBar(FindPassword);
        statusbar->setObjectName("statusbar");
        FindPassword->setStatusBar(statusbar);

        retranslateUi(FindPassword);

        QMetaObject::connectSlotsByName(FindPassword);
    } // setupUi

    void retranslateUi(QMainWindow *FindPassword)
    {
        FindPassword->setWindowTitle(QCoreApplication::translate("FindPassword", "MainWindow", nullptr));
        passwordRecoverypushButton->setText(QCoreApplication::translate("FindPassword", "password recovery", nullptr));
        passwordRecoveryUsernamelabel->setText(QCoreApplication::translate("FindPassword", "username        ", nullptr));
        passwordRecoveryUsernamelineEdit->setText(QString());
        passwordRecoveryUsernamelineEdit->setPlaceholderText(QCoreApplication::translate("FindPassword", "only must contain A_Z", nullptr));
        passwordRecoveryPhoneNumberlabel->setText(QCoreApplication::translate("FindPassword", "phone number", nullptr));
        passwordRecoveryPhoneNumberlineEdit->setPlaceholderText(QCoreApplication::translate("FindPassword", "example: 989123456789", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FindPassword: public Ui_FindPassword {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDPASSWORD_H
