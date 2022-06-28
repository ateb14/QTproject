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
    opponent = this;
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
void GamePlayer::setOpponent(GamePlayer *opponent_){this->opponent = opponent_;}
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
                    this, bulletPixmap[this->playerType], this->scene
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
    // CD减一，技能点数每秒回复10点。如果有狂暴buff，那么射击CD减二。
    if(this->hasBuff[BuffType::RAGE]) this->shootingCD = max(this->shootingCD-2, 0);
    else this->shootingCD = max(this->shootingCD-1, 0);
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
        if(((GameBullet *)obj)->bulletType==GameBullet::BulletType::ICEY)
        {
            this->addBuff(BuffType::FREEZE, BUFF_TIME);
        }
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
        if(obj->type!=GameObject::ObjectType::Ball) continue;
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
    // 给自己上磁铁的Buff
    this->addBuff(BuffType::MAGNET, BUFF_TIME);
}
void SantaClaus::skill()
{
    // To be done...
    // 发射三个冰块子弹
    double dist = 40;
    int dx = this->opponent->centerX()-this->centerX(),
        dy = this->opponent->centerY()-this->centerY();
    double dz = sqrt(dx*dx+dy*dy+1e-5);
    this->generatedObjects.push_back(
        new GameBullet(
            this->centerX()+dist*dx/dz, this->centerY()+dist*dy/dz,
            dx/dz*BULLET_SPEED, dy/dz*BULLET_SPEED,
            BULLET_RADIUS, BULLET_MASS, BULLET_DAMAGE, BULLET_TIME_TO_DESPAWN,
            this, bulletPixmap[0], this->scene
        ));
    double angle = 15*3.1415926/180;
    double new_sin = sin(angle)*dx/dz+cos(angle)*dy/dz,
           new_cos = cos(angle)*dx/dz-sin(angle)*dy/dz; // 希望是对的
    this->generatedObjects.push_back(
        new GameBullet(
            this->centerX()+dist*new_cos, this->centerY()+dist*new_sin,
            new_cos*BULLET_SPEED, new_sin*BULLET_SPEED,
            BULLET_RADIUS, BULLET_MASS, BULLET_DAMAGE, BULLET_TIME_TO_DESPAWN,
            this, bulletPixmap[0], this->scene
        ));
    angle = -angle;
    new_sin = sin(angle)*dx/dz+cos(angle)*dy/dz,
    new_cos = cos(angle)*dx/dz-sin(angle)*dy/dz; // 希望是对的
    this->generatedObjects.push_back(
        new GameBullet(
            this->centerX()+dist*new_cos, this->centerY()+dist*new_sin,
            new_cos*BULLET_SPEED, new_sin*BULLET_SPEED,
            BULLET_RADIUS, BULLET_MASS, BULLET_DAMAGE, BULLET_TIME_TO_DESPAWN,
            this, SSBulletPixmap[this->playerType], this->scene,
            GameBullet::BulletType::ICEY
        ));
}
void AngryBrother::skill()
{
    // To be done...
    this->addBuff(BuffType::SPEED, BUFF_TIME);
    this->addBuff(BuffType::RAGE, BUFF_TIME);
}
void GuoShen::skill()
{
    // To be done...
    double dist = 40;
    double vx[8] = {1, sqrt(2), 0, -sqrt(2), -1, -sqrt(2), 0, sqrt(2)},
            vy[8] = {0, sqrt(2), 1, sqrt(2), 0, -sqrt(2), -1, -sqrt(2)};
    double speed_factor = 3;
    double radius_factor = 5;
    double mass_factor = 5;
    for(int i = 0;i<8;i++)
    {
        this->generatedObjects.push_back(
            new GameBullet(
                this->centerX()+dist*vx[i], this->centerY()+dist*vy[i],
                vx[i]*BULLET_SPEED*speed_factor, vy[i]*BULLET_SPEED*speed_factor,
                BULLET_RADIUS*radius_factor, BULLET_MASS*mass_factor,
                BULLET_DAMAGE, BULLET_TIME_TO_DESPAWN,
                this, SSBulletPixmap[this->playerType], this->scene,
                GameBullet::BulletType::LAPTOP
            ));
    }
}
