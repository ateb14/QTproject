#ifndef GAMEITEM_H
#define GAMEITEM_H

#include "object.h"
#include "buff.h"

class GameItem : public GameObject
{
public:
    GameItem(int x, int y, const QPixmap *pixmap_, QGraphicsScene *scene_,
             BuffType buffType_, int remainTime_);

private:
    BuffType buffType;
    int remainTime;
    virtual void updateInGame();
    virtual void eatenBy(GameObject *obj);
    virtual void collides(GameObject *obj);
};

#endif // GAMEITEM_H
