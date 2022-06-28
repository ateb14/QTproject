#ifndef GAMEBULLET_H
#define GAMEBULLET_H

#include "object.h"

class GameBullet: public GameObject
{
public:
    enum BulletType{
        NORMAL, ICEY, LAPTOP
    } bulletType;
    GameBullet(int x, int y, double vx_, double vy_,
               int r, double m, int damage_, int timeToDespawn_,
               GameObject *owner_,
               const QPixmap *pixmap_, QGraphicsScene *scene_,
               BulletType bulletType_ = NORMAL);

private:
    // attributes
    int damage; // 子弹的伤害
    int timeToDespawn; // 子弹距离消失的时间（单位：帧）
    GameObject *owner; // 子弹的主人。（子弹不能打主人）
    // methods
    virtual void updateInGame();
    virtual void collides(GameObject *obj);
    virtual void eatenBy(GameObject *obj);
};

#endif // GAMEBULLET_H
