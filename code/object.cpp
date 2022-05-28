#include "object.h"

GameObject::GameObject(int x, int y, int r, double m, const QPixmap &pixmap_, QGraphicsScene *scene_)
    :QGraphicsPixmapItem(pixmap_.scaled(QSize(2*r, 2*r))){
    setPos(x-r, y-r); // setPos用的是左上角坐标，但是参数x和y是中心坐标，所以要减去偏移。
    scene = scene_;
    scene->addItem(this);
    isDead = false;
    radius = r;
    mass = m;
    setVelocity(0, 0);
}

GameObject::~GameObject()
{
    this->hide();
}

list<GameObject *> GameObject::getGeneratedObjects()
{
    return this->generatedObjects;
}

void GameObject::updateInGame()
{
    this->generatedObjects.clear(); // 清空生成的物体列表
    moveBy(vx, vy); // 按照当前速度移动
    if(isOutside(-GAME_DESPAWN_DIST, -GAME_DESPAWN_DIST,
                 scene->width()+GAME_DESPAWN_DIST, scene->height()+GAME_DESPAWN_DIST
                 )) isDead = true; // 越过边界太多的物体会被清除
    if(!isDead) update(); // 绘制图像
}

inline void GameObject::setVelocity(double vx_, double vy_){vx = vx_, vy = vy_;} // 设置物体速度

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
    // 如果两物体重叠，先把它们移开
    double m1 = this->mass, m2 = obj->mass;
    double x1 = this->centerX(), y1 = this->centerY(),
           x2 = obj->centerX(), y2 = obj->centerY();
    double dx = x2-x1+1e-5, dy = y2-y1;
    double dz = sqrt(dx*dx+dy*dy);
    double depth = (this->radius+obj->radius)-dz;
    double dz1 = -depth*m2/(m1+m2), dz2 = depth*m1/(m1+m2);
    double dx1 = dz1*dx/dz, dx2 = dz2*dx/dz,
           dy1 = dz1/(m1+m2)*dy/dz, dy2 = dz2*dy/dz;
    this->moveBy(dx1, dy1);
    obj->moveBy(dx2, dy2);

    // 计算并设置碰撞后速度
    double vx1 = this->vx, vy1 = this->vy, vx2 = obj->vx, vy2 = obj->vy;
    this->setVelocity((m1-m2)/(m1+m2)*vx1+(2*m2)/(m1+m2)*vx2,
                      (m1-m2)/(m1+m2)*vy1+(2*m2)/(m1+m2)*vy2);
    obj->setVelocity((2*m1)/(m1+m2)*vx1+(m2-m1)/(m1+m2)*vx2,
                     (2*m1)/(m1+m2)*vy1+(m2-m1)/(m1+m2)*vy2);

    this->debugInfo += "Bounced! ";
}

void GameObject::bounceWithBorder()
{
    double vx_new = this->vx, vy_new = this->vy;
    int x = this->centerX(), y = this->centerY();
    if(x-this->radius<=0) vx_new = max(vx_new, -vx_new);
    if(x+this->radius>=scene->width()) vx_new = min(vx_new, -vx_new);
    if(y-this->radius<=0) vy_new = max(vy_new, -vy_new);
    if(y+this->radius>=scene->height()) vy_new = min(vy_new, -vy_new);
    this->setVelocity(vx_new, vy_new);
}

void GameObject::eatenBy(GameObject *obj){} // 被另一物体吃掉（子弹或道具需要重写此方法）
void GameObject::takeDamage(int damage){} // 承受伤害（只有玩家或敌人需要此方法）

int GameObject::centerX(){return x()+radius;}
int GameObject::centerY(){return y()+radius;}
bool GameObject::isOutside(int x1, int y1, int x2, int y2) // 是否越过四个参数构成的长方形边界
{
    int cx = centerX(), cy = centerY();
    if(cx<x1 or cx>x2) return true;
    if(cy<y1 or cy>y2) return true;
    return false;
}
