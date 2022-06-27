#include "player.h"
#include "bullet.h"
#include "config.h"


ActionSet::ActionSet(){actions = 0;} // 空操作集合
bool ActionSet::contains(PlayerAction action){ // 集合中是否含某操作
    return actions&action;
}
void ActionSet::addAction(PlayerAction action) //向集合中添加操作
{
    actions |= action;
}

GamePlayer::GamePlayer(int x, int y,
                       const QPixmap *pixmap_,
                       QGraphicsScene *scene_,
                       GamePlayer *opponent_,
                       std::list<GameObject *> *gameObjects_):
    GameObject(x, y, PLAYER_RADIUS, PLAYER_MASS, pixmap_, scene_)
{
    type = ObjectType::Player;
    health = PLAYER_HEALTH;
    skillPoint = 0;
    speed = PLAYER_SPEED;
    shootingCD = 0;
    maxShootingCD = PLAYER_SHOOTING_CD;
    buffSet = {};
    opponent = opponent_;
    gameObjects = gameObjects_;
}

int GamePlayer::getHealth(){return this->health;}
void GamePlayer::addBuff(Buff *buff){this->buffSet.insert(buff);}

/* Keyboard Control */
void GamePlayer::playerAct(ActionSet action)
{
    // 判断Buff（SPEED, FREEZE, MAGNET, RAGE）
    bool hasBuff[Buff::BuffType::BUFF_TYPE_CNT];
    std::fill(hasBuff, hasBuff+Buff::BuffType::BUFF_TYPE_CNT, false);
    for(Buff *buff: this->buffSet)
    {
        hasBuff[buff->type] = true;
        buff->remainTime -= 1;
    }

    // Need to parse actions and do every action sequentially.

    // Walk
    double speedLimit = this->speed;
    if(hasBuff[Buff::BuffType::FREEZE]) speedLimit /= 2;
    if(hasBuff[Buff::BuffType::SPEED]) speedLimit *= 1.5;
    if(hasBuff[Buff::BuffType::RAGE]) speedLimit *= 1.5;

    double vx_new = this->vx, vy_new = this->vy;
    double ax = 0, ay = 0; // 加速度（我们有完美符合运动学的物理引擎！！！）
    if(action.contains(PlayerAction::LEFT)) ax--;
    if(action.contains(PlayerAction::RIGHT)) ax++;
    if(action.contains(PlayerAction::UP)) ay--;
    if(action.contains(PlayerAction::DOWN)) ay++;
    double az = sqrt(ax*ax+ay*ay);
    if(az>=1e-5)
    {
        vx_new += ax/az*PLAYER_ACCELERATION;
        vy_new += ay/az*PLAYER_ACCELERATION;
        if(vx_new*vx_new+vy_new*vy_new<=speedLimit*speedLimit)
        {
            this->setVelocity(vx_new, vy_new); // 不能超速
        }
    }

    // Shoot
    if(this->shootingCD<=0)
    {
        double vx_ = 0, vy_ = 0;
        if(action.contains(PlayerAction::LEFTSHOOT)) vx_--;
        if(action.contains(PlayerAction::RIGHTSHOOT)) vx_++;
        if(action.contains(PlayerAction::UPSHOOT)) vy_--;
        if(action.contains(PlayerAction::DOWNSHOOT)) vy_++;
        double vz_ = sqrt(vx_*vx_+vy_*vy_);
        if(vz_>=1e-5)
        {
            this->generatedObjects.push_back(
                new GameBullet(
                    this->centerX(), this->centerY(),
                    vx_/vz_*BULLET_SPEED, vy_/vz_*BULLET_SPEED,
                    BULLET_RADIUS, BULLET_MASS, BULLET_DAMAGE, BULLET_TIME_TO_DESPAWN,
                    this, bulletPixmap, this->scene
                ));
            this->shootingCD = this->maxShootingCD;
        }
    }

    // Skill
    if(this->skillPoint>=PLAYER_SKILL_POINT_LIMIT
       and action.contains(PlayerAction::SKILL))
    {
        this->skill();
    }
    // To be done...

}

void GamePlayer::updateInGame()
{
    // 遍历删除已经过时的Buff
    for (set<Buff *>::iterator it=this->buffSet.begin(); it!=this->buffSet.end();) {
        if ((*it)->remainTime<=0) {
            delete *it;
            it = this->buffSet.erase(it);
        } else {
            it++;
        }
    }

    // CD减一
    this->shootingCD = max(this->shootingCD-1, 0);

    // 人的速度会衰减
    double vx_new = this->vx*PLAYER_VELOCITY_DECAY, vy_new = this->vy*PLAYER_VELOCITY_DECAY;
    this->setVelocity(vx_new, vy_new);

    // 人会在边界反弹
    this->bounceWithBorder();

    // 更新调试信息
    this->debugInfo = QString::asprintf(
                "Player position: (%d, %d), \nplayer velocity: (%f, %f)",
                this->centerX(), this->centerY(), this->vx, this->vy
                );

    GameObject::updateInGame();
}

void GamePlayer::collides(GameObject *obj)
{
    switch(obj->type)
    {
    case Player:
        this->bounce(obj);
        return;
    case Bullet:
        this->bounce(obj);
        obj->eatenBy(this);
        return;
    case Ball:
        this->bounce(obj);
        return;
    case Item:
        obj->eatenBy(this);
        return;
    case Enemy:
        return;
    case Obstacle:
        this->bounce(obj);
        return;
    }
}

void GamePlayer::takeDamage(int damage)
{
    this->health -= damage;
    this->debugInfo += QString::asprintf("Player takes damage: %d! \n", damage);
    if(this->health<=0)
    {
        this->health = 0;
        this->debugInfo += QString::asprintf("Player died! \n");
    }
}

// 以下是磁铁buff的效果。
void GamePlayer::magnet()
{
    for(GameObject *obj: *(this->gameObjects))
    {
        double dx = this->centerX()-obj->centerX(),
               dy = this->centerY()-obj->centerY();
        double dz = sqrt(dx*dx+dy*dy+1e-5);
        double dvz = MAGNET_FORCE/this->mass;
        double dvx = dvz*dx/dz, dvy = dvz*dy/dz;
        obj->setVelocity(obj->vx+dvx, obj->vy+dvy);
    }
}

// 以下是各个角色的技能。
void LovingMan::skill()
{
    // To be done...
    //this->addBuff(new Buff);
}
void SantaClaus::skill()
{
    // To be done...
}
void AngryBrother::skill()
{
    // To be done...
}
void GuoShen::skill()
{
    // To be done...
}
