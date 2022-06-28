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

struct BoardInfo{
    int player1BigScore, player2BigScore;
    int player1SmallScore, player2SmallScore;
    int player1Health, player2Health;
    int player1Power, player2Power;
    bool player1Buff[BUFF_TYPE_CNT], player2Buff[BUFF_TYPE_CNT];
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
    void start(bool reviewMode = false);
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
    bool isPressingE,isPressingSemi;
    ActionSet parseKeyboard(int playerID);
    /* Texts */

    /* clock */
    QTimer *timer;
    int T;
    long long globalTime;

    /* Information Board */
    /* Advanced Information Board */
    bool AIBoardIsShow;
    QGraphicsTextItem * AIBoard;
    void showAIBoard();
    void hideAIBoard();
    /* Game Board */
    GameBoard *board; // abandonment
    BoardInfo boardInfo;
    /* win check */
    static int winFreeTime;
    /* music player*/
    QMediaPlayer *cheersPlayer;
    QMediaPlayer *backgroundPlayer;
    QMediaPlaylist *cheersPlaylist;
    QMediaPlaylist *backgroundPlaylist;
    /* game Setting */
    GameSettings gameSettings;
public:
    GameBoard *getBoard();
    void setTimerT(int T_=10);
    void setGlobalVars(PlayerType player1Type_=LOVEMAN, PlayerType player2Type_=LOVEMAN,
                       GameFormat gameFormat_=TWO_THREE, PlayerSpeed playerSpeed_=MIDDLE,bool enemyMode=true);
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
    void updateGameBoard();
    void createPlayers(PlayerType type1, PlayerType type2);

signals:
    void gameispause();
    void gamecontinue();
    void updateBigScore(int winner);
    void updateSmallScore(int winner);
    void updatePlayer1Health(double rate);
    void updatePlayer2Health(double rate);
    void updatePlayer1Power(double rate);
    void updatePlayer2Power(double rate);
    void addPlayer1Buff(int buff);
    void addPlayer2Buff(int buff);
    void removePlayer1Buff(int buff);
    void removePlayer2Buff(int buff);
    void refreshBoard(PlayerType player1, PlayerType player2);
};

#endif // !GAME_H
