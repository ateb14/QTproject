#include "player.h"

const int PLAYERHEALTH = 100;
const int SPEED = 5;
const double PLAYERMASS = 1145141919810;

bool ActionSet::contains(int action){return false;} // TO DO
ActionSet::ActionSet(long long actions_){actions = actions_;}

GamePlayer::GamePlayer(int x, int y, int r, const char *ImageSrc, QGraphicsScene *scene_)
:GameObject(x, y, r, PLAYERMASS, ImageSrc, scene_){
    health = PLAYERHEALTH;
    speed = SPEED;
}

/* Keyboard Control */
void GamePlayer::playerAct(ActionSet action)
{
    // Need to parse actions and do every action sequentially.
    if(action.contains(1));
    // TO DO
}

void GamePlayer::updateInGame()
{
    // NEED TO ADD CONTENT
    GameObject::updateInGame();
}
