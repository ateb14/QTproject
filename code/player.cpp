#include "player.h"

const int PLAYERHEALTH = 100;
const int SPEED = 5;

player::player(int x, int y, int w, int h, const char *ImageSrc, QGraphicsScene *scene_)
:object(x, y, w, h, ImageSrc, scene_){
    health = PLAYERHEALTH;
}

/* Keyboard Control */
void player::keyboardMove(KEYBOARD status){
    double xspeed = 0, yspeed = 0;
    if(CONTAIN(W,status) || CONTAIN(UP,status)){
        xspeed -= SPEED;
    }
    if(CONTAIN(A,status) || CONTAIN(LEFT,status)){
        yspeed -= SPEED;
    }
    if(CONTAIN(S,status) || CONTAIN(DOWN,status)){
        xspeed += SPEED;
    }
    if(CONTAIN(D,status) || CONTAIN(RIGHT,status)){
        yspeed += SPEED;
    }
    if(xspeed !=0 && yspeed != 0){
        xspeed /= sqrt(2);
        yspeed /= sqrt(2);
    }
    moveBy(yspeed,xspeed);
    update();
}
