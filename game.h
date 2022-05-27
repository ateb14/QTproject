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
#include <QDebug>
#include <object.h>
#include <player.h>
#include <windows.h>
#include <vector>

enum windowMode{
    HOME = 0,
    GAMING,
    MENU,
    SHOP,
    OPTION
};

class Game:public QGraphicsScene{
    Q_OBJECT
public:
    Game();
    friend class GameObject;
    friend class GamePlayer;
protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
protected slots:
    void updateGame();
    void quit();
    void start();
    void pause();
    void continueGame();
private:
    /* Window Mode */
    windowMode winMode;
    /* Keyboard Control Flags*/
    bool isPressingW,isPressingA,isPressingS,isPressingD;
    bool isPressingUp,isPressingDown,isPressingLeft,isPressingRight;
    /* Buttons */
    QGraphicsWidget *quitButton;
    QGraphicsWidget *startButton;
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

    /* objects */
    /* player */
    GamePlayer *player1, *player2;
    std::vector<GameObject> gameObjects;

    int getMoveHorizental(int playerID);
    int getMoveVertical(int playerID);
};

#endif // !GAME_H
