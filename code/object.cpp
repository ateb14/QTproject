#include "object.h"

GameObject::GameObject(int x, int y, int r, double m, const char *ImageSrc, QGraphicsScene *scene_)
    :QGraphicsPixmapItem(QPixmap(ImageSrc).scaled(QSize(r, r))){
    setPos(x-r, y-r); // setPos用的是左上角坐标，但是参数x和y是中心坐标，所以要减去偏移。
    scene = scene_;
    scene->addItem(this);
    isDead = false;
    radius = r;
    mass = m;
    setVelocity(0, 0);
}

/**
 * @brief GameObject::updateInGame 默认按照当前速度移动，然后判断是否应被清除，然后画在屏幕上
 */
void GameObject::updateInGame()
{
    moveBy(vx, vy); // 按照当前速度移动
    if(isOutside(-GAME_DESPAWN_DIST, -GAME_DESPAWN_DIST,
                 scene->width()+GAME_DESPAWN_DIST, scene->height()+GAME_DESPAWN_DIST
                 )) isDead = true; // 越过边界太多的物体会被清除
    if(!isDead) update();
}
inline void GameObject::setVelocity(int vx_, int vy_){vx = vx_, vy = vy_;} // 设置物体速度
bool GameObject::collideJudge(GameObject *obj) // 检测是否与另一物体碰撞
{
    double dx = obj->centerX()-this->centerX();
    double dy = obj->centerY()-this->centerY();
    double dz = sqrt(dx*dx+dy*dy);
    if(dz>=this->radius+obj->radius) return false; // 没有碰上
    else return true; // 碰上了
}
void GameObject::bounce(GameObject *obj) // 弹性碰撞
{
    double vx1 = this->vx, vy1 = this->vy, vx2 = obj->vx, vy2 = obj->vy;
    double m1 = this->mass, m2 = obj->mass;
    this->setVelocity((m1-m2)/(m1+m2)*vx1+(2*m2)/(m1+m2)*vx2,
                      (m1-m2)/(m1+m2)*vy1+(2*m2)/(m1+m2)*vy2);
    obj->setVelocity((2*m1)/(m1+m2)*vx1+(m2-m1)/(m1+m2)*vx2,
                     (2*m1)/(m1+m2)*vy1+(m2-m1)/(m1+m2)*vy2);
}
void GameObject::eatenBy(GameObject *obj){} // 被另一物体吃掉（子弹或道具需要重写此方法）

int GameObject::centerX(){return x()+radius;}
int GameObject::centerY(){return y()+radius;}
bool GameObject::isOutside(int x1, int y1, int x2, int y2) // 是否越过四个参数构成的长方形边界
{
    int cx = centerX(), cy = centerY();
    if(cx<x1 or cx>x2) return true;
    if(cy<y1 or cy>y2) return true;
    return false;
}
