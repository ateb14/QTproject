#-------------------------------------------------
#
# Project created by QtCreator 2022-05-26T13:52:28
#
#-------------------------------------------------

QT       += core gui
QT += multimedia # for music player

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = code
TEMPLATE = app


SOURCES += main.cpp\
    game.cpp \
    object.cpp \
    player.cpp \
    ball.cpp \
    obstacle.cpp \
    mybtn.cpp \
    mywindow.cpp

HEADERS  += \
    game.h \
    object.h \
    player.h \
    ball.h \
    obstacle.h \
    mybtn.h \
    mywindow.h

FORMS    +=

RESOURCES += \
    resources.qrc
