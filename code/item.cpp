#include "item.h"
#include "player.h"
#include "config.h"

GameItem::GameItem(int x, int y, const QPixmap *pixmap_, QGraphicsScene *scene_,
                   BuffType buffType_, int remainTime_):
    GameObject(x, y, ITEM_RADIUS, INFINITE_MASS, pixmap_, scene_)
{
    buffType = buffType_;
    remainTime = remainTime_;
}

void GameItem::eatenBy(GameObject *obj)
{
    if(obj->type!=ObjectType::Player) return;
    ((GamePlayer *)obj)->addBuff(this->buffType, BUFF_TIME);
}

void GameItem::collides(GameObject *obj)
{
    switch(obj->type)
    {
    case Obstacle:
        return;
    default:
        obj->collides(this);
    }
}

void GameItem::updateInGame()
{
    // 道具不会动
    this->setVelocity(0, 0);

    GameObject::updateInGame();
}
