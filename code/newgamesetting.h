#ifndef NEWGAMESETTING_H
#define NEWGAMESETTING_H

#include <QWidget>
#include "config.h"
#include <QPropertyAnimation>


class newGameSetting : public QWidget
{
    Q_OBJECT
public:
    explicit newGameSetting(QWidget *parent = 0);
    ~newGameSetting();
    void movein();
    void moveout();
    PlayerType player1Type, player2Type;
    GameFormat gameFormat;
    PlayerSpeed playerSpeed;
    bool enemyMode;

    QPropertyAnimation *ani1;
    QPropertyAnimation *ani2;
    QPropertyAnimation *ani3;
    QPropertyAnimation *ani4;
    QPropertyAnimation *ani5;
    QPropertyAnimation *ani6;
    QPropertyAnimation *ani7;
    QPropertyAnimation *ani8;
    QPropertyAnimation *ani9;
    QPropertyAnimation *ani10;
    QPropertyAnimation *ani11;
    QPropertyAnimation *ani12;
    QPropertyAnimation *ani13;
    QPropertyAnimation *ani14;
    QPropertyAnimation *ani15;
    QPropertyAnimation *ani16;


signals:
    void startgame();
    void backtomain();
public slots:
};

#endif // NEWGAMESETTING_H
