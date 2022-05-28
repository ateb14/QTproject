#ifndef OBJECT_H
#define OBJECT_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <cmath>
#include <iostream>
#include <list>
using namespace std;

class GameObject: public QGraphicsPixmapItem
{
public:
    GameObject(int x, int y, int r, double m, const QPixmap &pixmap_, QGraphicsScene *scene_);
    ~GameObject();

    bool isDead;
protected:
    // attributes
    static const int GAME_DESPAWN_DIST = 100;
    enum ObjectType
    {
        Player, Bullet, Ball, Item, Enemy, Obstacle
    } type;

    QGraphicsScene *scene;
    int radius; // 半径，碰撞的时候认为是圆形
    QString debugInfo = ""; // 当前帧的调试信息
    QString getDebugInfo();
    double vx, vy; // 速度
    double mass; // 质量（用于计算碰撞）
    int centerX();
    int centerY();
    bool isOutside(int x1, int y1, int x2, int y2); // 是否越过四个参数构成的长方形边界
    list<GameObject *> generatedObjects; // 当前帧，这个物体生成的新物体
    list<GameObject *> getGeneratedObjects();

    // methods
    virtual void updateInGame(); // 默认按照当前速度移动，然后判断是否应被清除
    inline void setVelocity(double vx_, double vy_); // 设置速度
    bool collideJudge(GameObject *obj); // 检测是否与另一物体碰撞
    virtual void collides(GameObject *obj) = 0; // 碰撞行为（每一类物体对于不同的对方物体行为不同）
    void bounce(GameObject *obj); // 完全弹性对心碰撞
    void bounceWithBorder(); // 碰到边界反弹（可选）
    virtual void eatenBy(GameObject *obj); // 被另一物体吃掉（子弹或道具需要重写此方法）
    virtual void takeDamage(int damage); // 承受伤害（只有玩家和敌人需要此方法）

    friend class Game;
    friend class GamePlayer;
    friend class GameBall;
    friend class GameBullet;
    friend class GameObstacle;
};

#endif // !OBJECT_H
