#include "ball.h"

const double BALL_VELOCITY_DECAY = 0.995;

GameBall::GameBall(int x, int y, int r, double m, const char *ImageSrc, QGraphicsScene *scene_):
    GameObject(x, y, r, m, ImageSrc, scene_)
{
    type = ObjectType::Ball;
}

void GameBall::updateInGame()
{
    this->setVelocity(this->vx*BALL_VELOCITY_DECAY, this->vy*BALL_VELOCITY_DECAY);
    // 球的速度会衰减
    GameObject::updateInGame();
}

void GameBall::collides(GameObject *obj)
{
    switch(obj->type)
    {
    case Player:
        obj->collides(this);
        return;
    case Bullet:
        this->bounce(obj);
        obj->isDead = true;
        return;
    case Ball:
        this->bounce(obj);
        return;
    case Item:
        return;
    case Enemy:
        this->bounce(obj);
        return;
    }
}
