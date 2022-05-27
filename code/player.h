#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"

struct ActionSet{
    long long actions;
    bool contains(int action);
    ActionSet(long long actions_);
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
