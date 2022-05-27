#ifndef OBJECT_H
#define OBJECT_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <cmath>
using namespace std;

class GameObject: public QGraphicsPixmapItem
{
public:
    GameObject(int x, int y, int r, double m, const char *ImageSrc, QGraphicsScene *scene_);
    bool isDead;
protected:
    // attributes
    static const int GAME_DESPAWN_DIST = 100;
    QGraphicsScene *scene;
    int radius; // 半径，碰撞的时候认为是圆形
    double vx, vy; // 速度
    double mass; // 质量（用于计算碰撞）
    int centerX();
    int centerY();
    bool isOutside(int x1, int y1, int x2, int y2); // 是否越过四个参数构成的长方形边界

    // methods
    virtual void updateInGame(); // 默认按照当前速度移动，然后判断是否应被清除
    inline void setVelocity(int vx_, int vy_); // 设置速度
    void collides(GameObject *obj); // 检测是否与另一物体碰撞，若确实撞到了，则进行碰撞过程（计算碰撞后速度）

    friend class Game;
};

#endif // !OBJECT_H
