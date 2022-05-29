#ifndef GAME_H
#define GAME_H

#include <QKeyEvent>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsWidget>
#include <QGraphicsTextItem>
#include <QMessageBox>
#include <QString>
#include <QTimer>
#include <QTime>
#include <QDebug>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <object.h>
#include <player.h>
#include <ball.h>
#include <config.h>
#include <obstacle.h>
#include <windows.h>
#include <board.h>
#include <list>
#include <iostream>
#include <fstream>
#include <vector>


enum windowMode{
    HOME = 0,
    GAMING,
    MENU,
    SHOP,
};

struct gameInfo{
    long long interval;
    ActionSet action1, action2;
};

class Game: public QGraphicsScene{
    Q_OBJECT
public:
    Game();
    friend class GameObject;
    friend class GamePlayer;
    friend class GameBall;

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
public slots:
    void updateGame();
    void endGame();
    void quit();
    void start();
    void pause(int ms=0);
    void continueGame();
private:
    /* Window Mode */
    windowMode winMode;
    /* Review Mode */
    static bool reviewMode;
    std::vector<gameInfo> gameInfos;
    long long infoReader;
    /* Keyboard Control Flags*/
    bool isPressingW,isPressingA,isPressingS,isPressingD;
    bool isPressingT,isPressingF,isPressingG,isPressingH;
    bool isPressingUp,isPressingDown,isPressingLeft,isPressingRight;
    bool isPressingL,isPressingComma,isPressingPeriod,isPressingDivision;
    ActionSet parseKeyboard(int playerID);
    /* Texts */

    /* clock */
    QTimer *timer;
    long long globalTime;

    /* Information Board */
    /* Advanced Information Board */
    bool AIBoardIsShow;
    QGraphicsTextItem * AIBoard;
    void showAIBoard();
    void hideAIBoard();
    /* Game Board */
    GameBoard *board;
    /* win check */
    static int winFreeTime;
    /* music player*/
    QMediaPlayer *cheersPlayer;
    QMediaPlayer *backgroundPlayer;
    QMediaPlaylist *cheersPlaylist;
    QMediaPlaylist *backgroundPlaylist;
public:
    GameBoard *getBoard();
private:

    /* objects */
    /* player */
    GamePlayer *player1, *player2;
    /* other */
    std::list<GameObject *> gameObjects;
    GameBall *ballptr;

    /* Update Checkers */
    void collisionCheck();
    void deadCheck();
    void goalCheck();
    void newObjectCheck();
    void updateInfoBoard();
signals:
    void gameispause();
    void gamecontinue();
};

#endif // !GAME_H
