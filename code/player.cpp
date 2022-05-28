#include "player.h"
#include "bullet.h"

const int PLAYER_HEALTH = 100;
const double PLAYER_SPEED = 3.0;
const double PLAYER_MASS = 2.0;
const double PLAYER_VELOCITY_DECAY = 0.97;
const double TIME_TO_REACH_MAX_SPEED = 20;
const double PLAYER_ACCELERATION = PLAYER_SPEED/TIME_TO_REACH_MAX_SPEED;
const int PLAYER_SHOOTING_CD = 1*100;

const double BULLET_SPEED = 7.0;
const double BULLET_MASS = 0.5;
const int BULLET_RADIUS = 10;
const int BULLET_DAMAGE = 10;
const int BULLET_TIME_TO_DESPAWN = 3*100;

const char bulletSrc[] = ":/art/bullet1.png";

ActionSet::ActionSet(){actions = 0;} // 空操作集合
bool ActionSet::contains(PlayerAction action){ // 集合中是否含某操作
    if(actions & action) return true;
    return false;
}
void ActionSet::addAction(PlayerAction action) //向集合中添加操作
{
    actions |= action;
}

GamePlayer::GamePlayer(int x, int y, int r,
                       const QPixmap &pixmap_, QPixmap *bulletPixmap_,
                       QGraphicsScene *scene_)
:GameObject(x, y, r, PLAYER_MASS, pixmap_, scene_){
    type = ObjectType::Player;
    health = PLAYER_HEALTH;
    speed = PLAYER_SPEED;
    shootingCD = 0;
    maxShootingCD = PLAYER_SHOOTING_CD;
    bulletPixmap = bulletPixmap_;
}

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
                    this, *(this->bulletPixmap), this->scene
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
    this->debugInfo += QString::asprintf(
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
