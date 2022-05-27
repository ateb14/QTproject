#ifndef OBJECT_H
#define OBJECT_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <cmath>
using namespace std;

class GameObject:public QGraphicsPixmapItem
{
public:
    GameObject(int x, int y, int r, const char *ImageSrc, QGraphicsScene *scene_);
protected:
    QGraphicsScene *scene;
    int radius; // 半径，碰撞的时候认为是圆形
    bool isDead;
    virtual void updateInGame();
    static const int GAME_DIST = 100;

};

#endif // !OBJECT_H
