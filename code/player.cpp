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

GamePlayer::GamePlayer(int x, int y, int r,
                       const QPixmap *pixmap_,
                       QGraphicsScene *scene_)
:GameObject(x, y, r, PLAYER_MASS, pixmap_, scene_){
    type = ObjectType::Player;
    health = PLAYER_HEALTH;
    speed = PLAYER_SPEED;
    shootingCD = 0;
    maxShootingCD = PLAYER_SHOOTING_CD;
    buffSet = BuffSet();
}

int GamePlayer::getHealth(){return this->health;}
BuffSet GamePlayer::getBuffSet(){return this->buffSet;}
void GamePlayer::addBuff(Buff buff){this->buffSet.addBuff(buff);}

/* Keyboard Control */
void GamePlayer::playerAct(ActionSet action)
{
    // Need to parse actions and do every action sequentially.

    // Walk
    double vx_new = this->vx, vy_new = this->vy;
    double ax = 0, ay = 0;
    if(action.contains(PlayerAction::LEFT)) ax--;
    if(action.contains(PlayerAction::RIGHT)) ax++;
    if(action.contains(PlayerAction::UP)) ay--;
    if(action.contains(PlayerAction::DOWN)) ay++;
    double az = sqrt(ax*ax+ay*ay);
    if(az>=1e-5)
    {
        vx_new += ax/az*PLAYER_ACCELERATION;
        vy_new += ay/az*PLAYER_ACCELERATION;
        if(vx_new*vx_new+vy_new*vy_new<=speed*speed) this->setVelocity(vx_new, vy_new); // 不能超速
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
    // To be done...

}

void GamePlayer::updateInGame()
{
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
