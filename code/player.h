#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"
typedef int KEYBOARD;
#define CONTAIN(x,status) bool(status & x)
#define ADDSTATUS(x,status) status |= x

enum keyboardSignal{
    W = 1,
    A = 1<<1,
    S = 1<<2,
    D = 1<<3,
    UP = 1<<4,
    DOWN = 1<<5,
    LEFT = 1<<6,
    RIGHT = 1<<7
};

class player:public object
{
public:
    player(int x, int y, int w, int h, const char *ImageSrc, QGraphicsScene *scene_);
private:
    int health;
public slots:
    void keyboardMove(KEYBOARD status);
};

#endif // !PLAYER_H
