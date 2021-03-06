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
    bullet.cpp \
    board.cpp \
    mybtn.cpp \
    mywindow.cpp \
    pausewindow.cpp \
    newgamesetting.cpp \
    pressanykeywindow.cpp \
    mylabel.cpp \
    boardwindow.cpp \
    cinemawindow.cpp \
    item.cpp

HEADERS  += \
    game.h \
    object.h \
    player.h \
    ball.h \
    obstacle.h \
    bullet.h \
    board.h \
    mybtn.h \
    mywindow.h \
    buff.h \
    config.h \
    pausewindow.h \
    newgamesetting.h \
    pressanykeywindow.h \
    mylabel.h \
    boardwindow.h \
    cinemawindow.h \
    item.h

FORMS    +=

RESOURCES += \
    resources.qrc

CONFIG += resources_big
