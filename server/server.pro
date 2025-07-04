QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    card.cpp \
    changeinfo.cpp \
    doublepair.cpp \
    fourofkind.cpp \
    fourrank.cpp \
    game.cpp \
    gamer.cpp \
    getuserinfo.cpp \
    goldenhand.cpp \
    handevaluator.cpp \
    handpattern.cpp \
    handutils.cpp \
    main.cpp \
    mainwindow.cpp \
    messyhand.cpp \
    mschand.cpp \
    myserver.cpp \
    mythread.cpp \
    orderhand.cpp \
    passrecovery.cpp \
    penthouse.cpp \
    series.cpp \
    signin.cpp \
    signup.cpp \
    singlepair.cpp \
    threekind.cpp

HEADERS += \
    card.h \
    changeinfo.h \
    doublepair.h \
    fourofkind.h \
    fourrank.h \
    game.h \
    gamer.h \
    getuserinfo.h \
    goldenhand.h \
    handevaluator.h \
    handorder.h \
    handpattern.h \
    handutils.h \
    mainwindow.h \
    messyhand.h \
    mschand.h \
    myserver.h \
    mythread.h \
    orderhand.h \
    passrecovery.h \
    penthouse.h \
    series.h \
    signin.h \
    signup.h \
    singlepair.h \
    threekind.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
