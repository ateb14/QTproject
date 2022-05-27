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

enum windowMode{
    HOME = 0,
    GAMING,
    MENU,
    SHOP,
    OPTION
};

class game:public QGraphicsScene{
    Q_OBJECT
public:
    game();
    friend class object;
    friend class player;
protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
protected slots:
    void updateTime();
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
    player *player1, *player2;
protected slots:
    void sendKeyboardMsg();
};

#endif // !GAME_H
