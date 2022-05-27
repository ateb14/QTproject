#ifndef GAMEBALL_H
#define GAMEBALL_H

#include "object.h"

class GameBall : public GameObject
{
public:
    GameBall(int x, int y, int r, double m, const char *ImageSrc, QGraphicsScene *scene_);

private:
    virtual void updateInGame();
    virtual void collides(GameObject *obj);
};

#endif // GAMEBALL_H
