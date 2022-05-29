#include "ball.h"
#include "config.h"

const double BALL_VELOCITY_DECAY = 0.985;

GameBall::GameBall(int x, int y, int r, double m, const QPixmap &pixmap, QGraphicsScene *scene_):
    GameObject(x, y, r, m, pixmap, scene_)
{
    type = ObjectType::Ball;
}

void GameBall::updateInGame()
{
    // 球的速度会衰减
    double vx_new = this->vx*BALL_VELOCITY_DECAY, vy_new = this->vy*BALL_VELOCITY_DECAY;
    this->setVelocity(vx_new, vy_new);
    // 球会在边界反弹
    this->bounceWithBorder();
    // 更新调试信息
    this->debugInfo = QString::asprintf(
                "Ball position: (%d, %d), \nball velocity: (%f, %f)",
                this->centerX(), this->centerY(), this->vx, this->vy
                );

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
    case Obstacle:
        this->bounce(obj);
        return;
    }
}
