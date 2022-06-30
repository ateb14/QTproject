#include "item.h"
#include "player.h"
#include "config.h"

GameItem::GameItem(int x, int y, const QPixmap *pixmap_, QGraphicsScene *scene_,
                   BuffType buffType_, int remainTime_, int buffTime_,
                   int gainHP_, int gainSkillPoint_):
    GameObject(x, y, ITEM_RADIUS, INFINITE_MASS, pixmap_, scene_)
{
    type = ObjectType::Item;
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
    player->health = min(player->health+this->gainHP,
                         player->maxHealth);
    player->skillPoint = min(player->skillPoint+this->gainSkillPoint,
                             PLAYER_SKILL_POINT_LIMIT);
    isDead = true;
    pickPlayer->play();
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
    --remainTime;
    if(remainTime <= 0) isDead = true;
    GameObject::updateInGame();
}
