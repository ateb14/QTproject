#include "obstacle.h"

const double INFINITE_MASS = 1919810.114514;

GameObstacle::GameObstacle(int x, int y, int r, const QPixmap &pixmap_, QGraphicsScene *scene_):
    GameObject(x, y, r, INFINITE_MASS, pixmap_, scene_)
{
    type = ObjectType::Obstacle;
}

void GameObstacle::updateInGame()
{
    // 障碍物不会动
    this->setVelocity(0, 0);

    GameObject::updateInGame();
}

void GameObstacle::collides(GameObject *obj)
{
    obj->collides(this);
}
