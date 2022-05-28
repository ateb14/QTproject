#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"

enum PlayerAction{
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
    long long actions;
    ActionSet();
    bool contains(PlayerAction action);
    void addAction(PlayerAction action);
};

class GamePlayer:public GameObject
{
public:
    GamePlayer(int x, int y, int r, const char *ImageSrc, QGraphicsScene *scene_);
    void playerAct(ActionSet action); // 接受一个操作集，由这个函数来进行所有操作
private:
    // attributes
    int health;
    double speed;

    // methods
    virtual void updateInGame();
    virtual void collides(GameObject *obj);

};

#endif // !PLAYER_H
