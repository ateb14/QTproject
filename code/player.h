#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"

class PlayerObject:public GameObject
{
public:
    PlayerObject(int x, int y, int w, int h, const char *ImageSrc, QGraphicsScene *scene_);
private:
    int health;
    int speed;
    virtual void updateInGame();
    void moveInGame(double x, double y);
friend class Game;
};

#endif // !PLAYER_H
