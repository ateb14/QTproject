#ifndef NEWGAMESETTING_H
#define NEWGAMESETTING_H

#include <QWidget>
#include "config.h"

class newGameSetting : public QWidget
{
    Q_OBJECT
public:
    explicit newGameSetting(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void movein();
    void moveout();
    PlayerType player1Type, player2Type;
    GameFormat gameFormat;
    PlayerSpeed playerSpeed;
    bool enemyMode;

signals:
    void startgame();
    void backtomain();
public slots:
};

#endif // NEWGAMESETTING_H
