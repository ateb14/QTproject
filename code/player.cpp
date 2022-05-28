#include "player.h"

const int PLAYERHEALTH = 100;
const double SPEED = 3.0;
const double PLAYERMASS = 2.0;
const double PLAYER_VELOCITY_DECAY = 0.97;
const double TIME_TO_REACH_MAX_SPEED = 20;
const double PLAYER_ACCELERATION = SPEED/TIME_TO_REACH_MAX_SPEED;

ActionSet::ActionSet(){actions = 0;} // 空操作集合
bool ActionSet::contains(PlayerAction action){ // 集合中是否含某操作
    if(actions & action) return true;
    return false;
}
void ActionSet::addAction(PlayerAction action) //向集合中添加操作
{
    actions |= action;
}

GamePlayer::GamePlayer(int x, int y, int r, const char *ImageSrc, QGraphicsScene *scene_)
:GameObject(x, y, r, PLAYERMASS, ImageSrc, scene_){
    type = ObjectType::Player;
    health = PLAYERHEALTH;
    speed = SPEED;
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
    // To be done...

}

void GamePlayer::updateInGame()
{
    // 人的速度会衰减
    double vx_new = this->vx*PLAYER_VELOCITY_DECAY, vy_new = this->vy*PLAYER_VELOCITY_DECAY;
    this->setVelocity(vx_new, vy_new);
    // 人会在边界反弹
    this->bounceWithBorder();
    // NEED TO ADD CONTENT

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
