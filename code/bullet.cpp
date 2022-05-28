#include "bullet.h"

GameBullet::GameBullet(int x, int y, double vx_, double vy_,
                       int r, double m, int damage_, int timeToDespawn_,
                       GameObject *owner_,
                       const char *ImageSrc, QGraphicsScene *scene_):
    GameObject(x, y, r, m, ImageSrc, scene_)
{
    this->setVelocity(vx_, vy_);
    damage = damage_;
    timeToDespawn = timeToDespawn_;
    owner = owner_;
    type = ObjectType::Bullet;
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
}

void GameBullet::collides(GameObject *obj)
{
    switch(obj->type)
    {
    case Player:
        if(obj==this->owner) return; //子弹不能打主人
        obj->collides(this); // 暂时认为子弹有击退效果
        this->eatenBy(obj);
        return;
    case Bullet:
        return;
    case Ball:
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
