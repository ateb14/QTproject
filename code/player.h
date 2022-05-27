#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"

class GamePlayer:public GameObject
{
public:
    GamePlayer(int x, int y, int r, const char *ImageSrc, QGraphicsScene *scene_);
private:
    int health;
    int speed;
    virtual void updateInGame();
    void moveInGame(double x, double y);
friend class Game;
};

#endif // !PLAYER_H
