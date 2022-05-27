#include "object.h"

GameObject::GameObject(int x, int y, int r, const char *ImageSrc, QGraphicsScene *scene_)
    :QGraphicsPixmapItem(QPixmap(ImageSrc).scaled(QSize(r, r))){
    setPos(x,y);
    scene = scene_;
    scene->addItem(this);
    isDead = false;
    radius = r;
}

void GameObject::updateInGame()
{
    update();
    if(x()<-GAME_DIST or x()>scene->width()+GAME_DIST
       or y()<-GAME_DIST or y()>scene->height()+GAME_DIST) isDead = true;
}
