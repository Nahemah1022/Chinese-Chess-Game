#-------------------------------------------------
#
# Project created by QtCreator 2019-04-11T19:59:18
#
#-------------------------------------------------
QT       += network
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pd2-boardgame
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    chess.cpp \
    soldier.cpp \
    fire.cpp \
    mouse_tracking.cpp \
    button_tracking.cpp \
    general.cpp \
    staff.cpp \
    car.cpp \
    defender.cpp \
    horse.cpp \
    menuwindow.cpp \
    editorwindow.cpp \
    client.cpp \
    server.cpp \

HEADERS += \
        mainwindow.h \
    chess.h \
    soldier.h \
    fire.h \
    horse.h \
    car.h \
    staff.h \
    defender.h \
    general.h \
    mouse_tracking.h \
    button_tracking.h \
    menuwindow.h \
    editorwindow.h \
    client.h \
    server.h \

FORMS += \
        mainwindow.ui \
    menuwindow.ui \
    editorwindow.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
