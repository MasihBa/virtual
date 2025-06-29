/********************************************************************************
** Form generated from reading UI file 'menu.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENU_H
#define UI_MENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Menu
{
public:
    QWidget *centralwidget;
    QLabel *pofferlabel;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_5;
    QPushButton *startGameButton;
    QSpacerItem *verticalSpacer;
    QPushButton *historyButton;
    QSpacerItem *verticalSpacer_2;
    QPushButton *changeInfoButton;
    QSpacerItem *verticalSpacer_3;
    QPushButton *logOutButton;
    QSpacerItem *verticalSpacer_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QWidget *Menu)
    {
        if (Menu->objectName().isEmpty())
            Menu->setObjectName("Menu");
        Menu->resize(800, 600);
        centralwidget = new QWidget(Menu);
        centralwidget->setObjectName("centralwidget");
        pofferlabel = new QLabel(centralwidget);
        pofferlabel->setObjectName("pofferlabel");
        pofferlabel->setGeometry(QRect(310, 40, 161, 20));
        pofferlabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(250, 110, 281, 374));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        startGameButton = new QPushButton(widget);
        startGameButton->setObjectName("startGameButton");

        verticalLayout->addWidget(startGameButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        historyButton = new QPushButton(widget);
        historyButton->setObjectName("historyButton");

        verticalLayout->addWidget(historyButton);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        changeInfoButton = new QPushButton(widget);
        changeInfoButton->setObjectName("changeInfoButton");

        verticalLayout->addWidget(changeInfoButton);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        logOutButton = new QPushButton(widget);
        logOutButton->setObjectName("logOutButton");

        verticalLayout->addWidget(logOutButton);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        menubar = new QMenuBar(Menu);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        statusbar = new QStatusBar(Menu);
        statusbar->setObjectName("statusbar");

        retranslateUi(Menu);

        QMetaObject::connectSlotsByName(Menu);
    } // setupUi

    void retranslateUi(QWidget *Menu)
    {
        Menu->setWindowTitle(QCoreApplication::translate("Menu", "MainWindow", nullptr));
        pofferlabel->setText(QCoreApplication::translate("Menu", "poffer", nullptr));
        startGameButton->setText(QCoreApplication::translate("Menu", "start game", nullptr));
        historyButton->setText(QCoreApplication::translate("Menu", "history", nullptr));
        changeInfoButton->setText(QCoreApplication::translate("Menu", "change info", nullptr));
        logOutButton->setText(QCoreApplication::translate("Menu", "log out", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Menu: public Ui_Menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENU_H
