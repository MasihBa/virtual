/********************************************************************************
** Form generated from reading UI file 'changeInfo.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGEINFO_H
#define UI_CHANGEINFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChangeInfo
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *firstNamelabel;
    QLineEdit *firstNamelineEdit;
    QSpacerItem *verticalSpacer;
    QFormLayout *formLayout_2;
    QLabel *lastNamelabel;
    QLineEdit *lastNamelineEdit;
    QSpacerItem *verticalSpacer_2;
    QFormLayout *formLayout_3;
    QLabel *usernamelabel;
    QLineEdit *usernamelineEdit;
    QSpacerItem *verticalSpacer_4;
    QFormLayout *formLayout_4;
    QLabel *passwordlabel;
    QLineEdit *passwordlineEdit;
    QSpacerItem *verticalSpacer_3;
    QFormLayout *formLayout_7;
    QLabel *phonelabel;
    QLineEdit *phonelineEdit;
    QSpacerItem *verticalSpacer_5;
    QFormLayout *formLayout_6;
    QLabel *emaillabel;
    QLineEdit *emaillineEdit;
    QPushButton *saveButton;
    QPushButton *cancelButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ChangeInfo)
    {
        if (ChangeInfo->objectName().isEmpty())
            ChangeInfo->setObjectName("ChangeInfo");
        ChangeInfo->resize(800, 600);
        centralwidget = new QWidget(ChangeInfo);
        centralwidget->setObjectName("centralwidget");
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(270, 0, 233, 452));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        firstNamelabel = new QLabel(layoutWidget);
        firstNamelabel->setObjectName("firstNamelabel");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, firstNamelabel);

        firstNamelineEdit = new QLineEdit(layoutWidget);
        firstNamelineEdit->setObjectName("firstNamelineEdit");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, firstNamelineEdit);


        verticalLayout->addLayout(formLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName("formLayout_2");
        lastNamelabel = new QLabel(layoutWidget);
        lastNamelabel->setObjectName("lastNamelabel");

        formLayout_2->setWidget(0, QFormLayout::ItemRole::LabelRole, lastNamelabel);

        lastNamelineEdit = new QLineEdit(layoutWidget);
        lastNamelineEdit->setObjectName("lastNamelineEdit");

        formLayout_2->setWidget(0, QFormLayout::ItemRole::FieldRole, lastNamelineEdit);


        verticalLayout->addLayout(formLayout_2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        formLayout_3 = new QFormLayout();
        formLayout_3->setObjectName("formLayout_3");
        usernamelabel = new QLabel(layoutWidget);
        usernamelabel->setObjectName("usernamelabel");

        formLayout_3->setWidget(0, QFormLayout::ItemRole::LabelRole, usernamelabel);

        usernamelineEdit = new QLineEdit(layoutWidget);
        usernamelineEdit->setObjectName("usernamelineEdit");

        formLayout_3->setWidget(0, QFormLayout::ItemRole::FieldRole, usernamelineEdit);


        verticalLayout->addLayout(formLayout_3);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        formLayout_4 = new QFormLayout();
        formLayout_4->setObjectName("formLayout_4");
        passwordlabel = new QLabel(layoutWidget);
        passwordlabel->setObjectName("passwordlabel");

        formLayout_4->setWidget(0, QFormLayout::ItemRole::LabelRole, passwordlabel);

        passwordlineEdit = new QLineEdit(layoutWidget);
        passwordlineEdit->setObjectName("passwordlineEdit");

        formLayout_4->setWidget(0, QFormLayout::ItemRole::FieldRole, passwordlineEdit);


        verticalLayout->addLayout(formLayout_4);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        formLayout_7 = new QFormLayout();
        formLayout_7->setObjectName("formLayout_7");
        phonelabel = new QLabel(layoutWidget);
        phonelabel->setObjectName("phonelabel");

        formLayout_7->setWidget(0, QFormLayout::ItemRole::LabelRole, phonelabel);

        phonelineEdit = new QLineEdit(layoutWidget);
        phonelineEdit->setObjectName("phonelineEdit");

        formLayout_7->setWidget(0, QFormLayout::ItemRole::FieldRole, phonelineEdit);


        verticalLayout->addLayout(formLayout_7);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        formLayout_6 = new QFormLayout();
        formLayout_6->setObjectName("formLayout_6");
        emaillabel = new QLabel(layoutWidget);
        emaillabel->setObjectName("emaillabel");

        formLayout_6->setWidget(0, QFormLayout::ItemRole::LabelRole, emaillabel);

        emaillineEdit = new QLineEdit(layoutWidget);
        emaillineEdit->setObjectName("emaillineEdit");

        formLayout_6->setWidget(0, QFormLayout::ItemRole::FieldRole, emaillineEdit);


        verticalLayout->addLayout(formLayout_6);

        saveButton = new QPushButton(centralwidget);
        saveButton->setObjectName("saveButton");
        saveButton->setGeometry(QRect(580, 500, 83, 29));
        cancelButton = new QPushButton(centralwidget);
        cancelButton->setObjectName("cancelButton");
        cancelButton->setGeometry(QRect(680, 500, 83, 29));
        ChangeInfo->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ChangeInfo);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        ChangeInfo->setMenuBar(menubar);
        statusbar = new QStatusBar(ChangeInfo);
        statusbar->setObjectName("statusbar");
        ChangeInfo->setStatusBar(statusbar);

        retranslateUi(ChangeInfo);

        QMetaObject::connectSlotsByName(ChangeInfo);
    } // setupUi

    void retranslateUi(QMainWindow *ChangeInfo)
    {
        ChangeInfo->setWindowTitle(QCoreApplication::translate("ChangeInfo", "MainWindow", nullptr));
        firstNamelabel->setText(QCoreApplication::translate("ChangeInfo", "first name", nullptr));
        lastNamelabel->setText(QCoreApplication::translate("ChangeInfo", "last name", nullptr));
        usernamelabel->setText(QCoreApplication::translate("ChangeInfo", "username", nullptr));
        passwordlabel->setText(QCoreApplication::translate("ChangeInfo", "passowrd ", nullptr));
        phonelabel->setText(QCoreApplication::translate("ChangeInfo", "phone number", nullptr));
        emaillabel->setText(QCoreApplication::translate("ChangeInfo", "email", nullptr));
        saveButton->setText(QCoreApplication::translate("ChangeInfo", "save", nullptr));
        cancelButton->setText(QCoreApplication::translate("ChangeInfo", "cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChangeInfo: public Ui_ChangeInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGEINFO_H
