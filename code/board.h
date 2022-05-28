#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>

enum gameModeEnum{
    FOOTBALL = 0
};

class GameBoard:public QGraphicsScene{
    Q_OBJECT
public:
    friend class Game;
    GameBoard();
private:
    gameModeEnum gameMode;
};

#endif // BOARD_H
