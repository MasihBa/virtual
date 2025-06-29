/********************************************************************************
** Form generated from reading UI file 'waiting.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WAITING_H
#define UI_WAITING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Waiting
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *topSpacer;
    QLabel *waitingLabel;
    QLabel *playersCountLabel;
    QSpacerItem *middleSpacer;
    QPushButton *cancelButton;
    QSpacerItem *bottomSpacer;

    void setupUi(QWidget *Waiting)
    {
        if (Waiting->objectName().isEmpty())
            Waiting->setObjectName("Waiting");
        Waiting->resize(400, 300);
        verticalLayout = new QVBoxLayout(Waiting);
        verticalLayout->setSpacing(20);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(50, 50, 50, 50);
        topSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(topSpacer);

        waitingLabel = new QLabel(Waiting);
        waitingLabel->setObjectName("waitingLabel");
        waitingLabel->setAlignment(Qt::AlignCenter);
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        waitingLabel->setFont(font);

        verticalLayout->addWidget(waitingLabel);

        playersCountLabel = new QLabel(Waiting);
        playersCountLabel->setObjectName("playersCountLabel");
        playersCountLabel->setAlignment(Qt::AlignCenter);
        QFont font1;
        font1.setPointSize(12);
        playersCountLabel->setFont(font1);

        verticalLayout->addWidget(playersCountLabel);

        middleSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(middleSpacer);

        cancelButton = new QPushButton(Waiting);
        cancelButton->setObjectName("cancelButton");
        cancelButton->setMinimumSize(QSize(100, 35));

        verticalLayout->addWidget(cancelButton);

        bottomSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(bottomSpacer);


        retranslateUi(Waiting);

        QMetaObject::connectSlotsByName(Waiting);
    } // setupUi

    void retranslateUi(QWidget *Waiting)
    {
        Waiting->setWindowTitle(QCoreApplication::translate("Waiting", "Waiting for Players", nullptr));
        waitingLabel->setText(QCoreApplication::translate("Waiting", "Waiting for players...", nullptr));
        playersCountLabel->setText(QCoreApplication::translate("Waiting", "Players: 0/4", nullptr));
        cancelButton->setText(QCoreApplication::translate("Waiting", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Waiting: public Ui_Waiting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WAITING_H
