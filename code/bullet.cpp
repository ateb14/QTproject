#include "bullet.h"
#include "buff.h"

GameBullet::GameBullet(int x, int y, double vx_, double vy_,
                       int r, double m, int damage_, int timeToDespawn_,
                       GameObject *owner_,
                       const QPixmap *pixmap, QGraphicsScene *scene_, BulletType bulletType_):
    GameObject(x, y, r, m, pixmap, scene_)
{
    this->setVelocity(vx_, vy_);
    damage = damage_;
    timeToDespawn = timeToDespawn_;
    owner = owner_;
    type = ObjectType::Bullet;
    bulletType = bulletType_;
}

void GameBullet::updateInGame()
{
    this->timeToDespawn -= 1;

    GameObject::updateInGame();
}

void GameBullet::eatenBy(GameObject *obj)
{
    if(obj==this->owner) return; // 子弹不能打主人
    obj->takeDamage(this->damage);
    this->isDead = true;
}

void GameBullet::collides(GameObject *obj)
{
    switch(obj->type)
    {
    case Player:
        obj->collides(this);
        return;
    case Bullet:
        return;
    case Ball:
        if(this->bulletType==LAPTOP) return; // 郭神的电脑不能砸球
        this->bounce(obj);
        this->isDead = true;
        return;
    case Item:
        return;
    case Enemy:
        this->bounce(obj); // 暂时认为子弹有击退效果
        this->eatenBy(obj);
        return;
    case Obstacle:
        this->isDead = true;
        return;
    }
}
