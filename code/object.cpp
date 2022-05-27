#include "object.h"

object::object(int x, int y, int w, int h, const char *ImageSrc, QGraphicsScene *scene_)
    :QGraphicsPixmapItem(QPixmap(ImageSrc).scaled(QSize(w,h))){
    setPos(x,y);
    scene = scene_;
    scene->addItem(this);
}


