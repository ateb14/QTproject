#ifndef PLAYER_H
#define PLAYER_H
;
#include "object.h"

typedef long long PlayerAction;

enum{
    /* movement */
    UP = 1,
    LEFT = 1<<1,
    DOWN = 1<<2,
    RIGHT = 1<<3,
    /* shoot */
    UPSHOOT = 1<<4,
    LEFTSHOOT = 1<<5,
    DOWNSHOOT = 1<<6,
    RIGHTSHOOT = 1<<7,
    /* Speed Factors */
    CONTROLSLOW = 1<<8,
    /* Special */
    SKILL = 1<<9,
    ITEM = 1<<10,
};

struct ActionSet{
    PlayerAction actions;
    bool contains(PlayerAction action);
    ActionSet(PlayerAction actions_);
};

class GamePlayer:public GameObject
{
public:
    GamePlayer(int x, int y, int r, const char *ImageSrc, QGraphicsScene *scene_);
private:
    // attributes
    int health;
    int speed;

    // methods
    void playerAct(ActionSet action); // 接受一个操作集，由这个函数来进行所有操作
    virtual void updateInGame();

    friend class Game;
};

#endif // !PLAYER_H
