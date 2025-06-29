QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += network

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cardWidget.cpp \
    changeinfo.cpp \
    findpassword.cpp \
    gameUI.cpp \
    hsitory.cpp \
    ipgetter.cpp \
    main.cpp \
    mainwindow.cpp \
    menu.cpp \
    signin.cpp \
    signup.cpp \
    socketHandler.cpp \
    user.cpp \
    waiting.cpp

HEADERS += \
    cardWidget.h \
    changeinfo.h \
    findpassword.h \
    gameUI.h \
    history.h \
    ipgetter.h \
    mainwindow.h\
    menu.h \
    signin.h \
    signup.h \
    socketHandler.h \
    user.h \
    waiting.h

FORMS += \
    changeInfo.ui \
    findpassword.ui \
    gameUI.ui \
    history.ui \
    mainwindow.ui \
    menu.ui \
    signin.ui \
    signup.ui \
    waiting.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc \
    resources.qrc
