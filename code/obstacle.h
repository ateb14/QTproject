#ifndef GAMEOBSTACLE_H
#define GAMEOBSTACLE_H

#include "object.h"

class GameObstacle : public GameObject
{
public:
    GameObstacle(int x, int y, int r, const char *ImageSrc, QGraphicsScene *scene_);

private:
    virtual void updateInGame();
    virtual void collides(GameObject *obj);
};

#endif // GAMEOBSTACLE_H
