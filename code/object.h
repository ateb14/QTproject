#ifndef OBJECT_H
#define OBJECT_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <cmath>

class object:public QGraphicsPixmapItem
{
public:
    object(int x, int y, int w, int h, const char *ImageSrc, QGraphicsScene *scene_);
private:
    QGraphicsScene *scene;

};

#endif // !OBJECT_H
