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
    skillPoint = PLAYER_SKILL_POINT_LIMIT;
    speed = PLAYER_SPEED;
    shootingCD = 0;
    maxShootingCD = PLAYER_SHOOTING_CD;
    skillPointGainCD = maxSkillPointGainCD = PLAYER_SKILL_POINT_GAIN_CD;
    fill(hasBuff, hasBuff+BuffType::BUFF_TYPE_CNT, 0);
    opponent = opponent_;
    gameObjects = gameObjects_;
}

void GamePlayer::reset(int x, int y)
{
    isDead = false;
    setPos(x-radius, y-radius);
    setVelocity(0, 0);
    health = PLAYER_HEALTH;
    skillPoint = PLAYER_SKILL_POINT_LIMIT;
    speed = PLAYER_SPEED;
    shootingCD = 0;
    maxShootingCD = PLAYER_SHOOTING_CD;
    skillPointGainCD = maxSkillPointGainCD = PLAYER_SKILL_POINT_GAIN_CD;
    fill(hasBuff, hasBuff+BuffType::BUFF_TYPE_CNT, 0);
}

int GamePlayer::getHealth(){return this->health;}
int GamePlayer::getSkillPoint(){return this->skillPoint;}
int *GamePlayer::getBuffSet(){return this->hasBuff;}
void GamePlayer::addBuff(BuffType buffType, int time)
{
    this->hasBuff[buffType] = max(this->hasBuff[buffType], time);
}

/* Keyboard Control */
void GamePlayer::playerAct(ActionSet action)
{
    // Need to parse actions and do every action sequentially.

    // Walk
    double speedLimit = this->speed;
    if(this->hasBuff[BuffType::FREEZE]) speedLimit /= 2;
    if(this->hasBuff[BuffType::SPEED]) speedLimit *= 1.5;
    if(this->hasBuff[BuffType::RAGE]) speedLimit *= 1.5;

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
        this->skillPoint = 0;
    }
    // To be done...

}

void GamePlayer::updateInGame()
{
    // CD减一，技能点数每秒回复10点
    this->shootingCD = max(this->shootingCD-1, 0);
    this->skillPointGainCD -= 1;
    if(this->skillPointGainCD<=0)
    {
        this->skillPoint = min(this->skillPoint+1, PLAYER_SKILL_POINT_LIMIT);
        this->skillPointGainCD = this->maxSkillPointGainCD;
    }

    // Buff持续时间减一
    for(int buffType = 0;buffType<BuffType::BUFF_TYPE_CNT;buffType++)
    {
        hasBuff[buffType] = max(0, hasBuff[buffType]-1);
    }

    // 人的速度会衰减
    double vx_new = this->vx*PLAYER_VELOCITY_DECAY, vy_new = this->vy*PLAYER_VELOCITY_DECAY;
    this->setVelocity(vx_new, vy_new);

    // 人会在边界反弹
    this->bounceWithBorder();

    // 人吸引游戏物体（有buff时）
    if(this->hasBuff[BuffType::MAGNET])
    {
        this->magnet(); // 佛祖保佑过过过
    }

    // 更新调试信息
    this->debugInfo = QString::asprintf(
                "Player position: (%d, %d), \nplayer velocity: (%f, %f), \nHP: %d/100, Skill: %d/100",
                this->centerX(), this->centerY(), this->vx, this->vy, this->health, this->skillPoint
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
        double force = MAGNET_FORCE/dz;
        double dvz = force/obj->mass;
        double dvx = dvz*dx/dz, dvy = dvz*dy/dz;
        obj->setVelocity(obj->vx+dvx, obj->vy+dvy);
        double dvz0 = force/this->mass;
        double dvx0 = -dvz0*dx/dz, dvy0 = -dvz0*dy/dz;
        this->setVelocity(this->vx+dvx0, this->vy+dvy0);
    }
}

// 以下是各个角色的技能。
void LovingMan::skill()
{
    // To be done...
    this->addBuff(BuffType::MAGNET, BUFF_TIME);
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
