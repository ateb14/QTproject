#ifndef OBJECT_H
#define OBJECT_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <cmath>

class GameObject:public QGraphicsPixmapItem
{
public:
    GameObject(int x, int y, int w, int h, const char *ImageSrc, QGraphicsScene *scene_);
private:
    QGraphicsScene *scene;
    virtual void updateInGame();

};

#endif // !OBJECT_H
