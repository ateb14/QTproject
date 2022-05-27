#include "player.h"

const int PLAYERHEALTH = 100;
const int SPEED = 5;

GamePlayer::GamePlayer(int x, int y, int r, const char *ImageSrc, QGraphicsScene *scene_)
:GameObject(x, y, r, ImageSrc, scene_){
    health = PLAYERHEALTH;
    speed = SPEED;
}

/* Keyboard Control */
void GamePlayer::moveInGame(double horizontal, double vertical){
    double z = sqrt(horizontal*horizontal+vertical*vertical);
    if(z<1e-5) return;
    horizontal = horizontal/z*speed;
    vertical = vertical/z*speed;
    moveBy(horizontal, -vertical);
}

void GamePlayer::updateInGame()
{

    // NEED TO ADD CONTENT
    update();
}
