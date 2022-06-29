#include "item.h"
#include "player.h"
#include "config.h"

GameItem::GameItem(int x, int y, const QPixmap *pixmap_, QGraphicsScene *scene_,
                   BuffType buffType_, int remainTime_, int buffTime_,
                   int gainHP_, int gainSkillPoint_):
    GameObject(x, y, ITEM_RADIUS, INFINITE_MASS, pixmap_, scene_)
{
    buffType = buffType_;
    remainTime = remainTime_;
    buffTime = buffTime_;
    gainHP = gainHP_;
    gainSkillPoint = gainSkillPoint_;
}

void GameItem::eatenBy(GameObject *obj)
{
    if(obj->type!=ObjectType::Player) return;
    GamePlayer *player = (GamePlayer *)obj;
    player->addBuff(this->buffType, buffTime);
    player->health = max(player->health+this->gainHP,
                         player->maxHealth);
    player->skillPoint = max(player->skillPoint+this->gainSkillPoint,
                             PLAYER_SKILL_POINT_LIMIT);
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
