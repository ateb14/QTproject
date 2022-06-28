#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"
#include "buff.h"
#include<set>

enum PlayerAction{
    /* movement */
    UP = 1,
    LEFT = 1<<1,
    DOWN = 1<<2,
    RIGHT = 1<<3,
    /* shoot */
    UPSHOOT = 1<<4,
    LEFTSHOOT = 1<<5,
    DOWNSHOOT = 1<<6,
    RIGHTSHOOT = 1<<7,
    /* Speed Factors */
    CONTROLSLOW = 1<<8,
    /* Special */
    SKILL = 1<<9,
    ITEM = 1<<10,
};
struct ActionSet{
    long long actions;
    ActionSet();
    bool contains(PlayerAction action);
    void addAction(PlayerAction action);
};

class GamePlayer: public GameObject
{
public:
    GamePlayer(int x, int y,
               const QPixmap *pixmap_,
               QGraphicsScene *scene_,
               GamePlayer *opponent_,
               std::list<GameObject *> *gameObjects_);
    void playerAct(ActionSet action); // 接受一个操作集，由这个函数来进行所有操作
    void reset(int x, int y); // 重置玩家的所有状态
    // proprety
    enum PlayerType{
        LOVING_MAN, SANTA_CLAUS, ANGRY_BROTHER, GUO_SHEN
    } playerType;

    int getHealth();
    int getSkillPoint();
    int *getBuffSet();
    void addBuff(BuffType buffType, int time);

private:
    // attributes
    int health;
    int skillPoint;
    double speed; // 最高速度（单位：像素/帧）
    int shootingCD; // 当前设计CD（单位：帧）
    int maxShootingCD; // 射击总CD（单位：帧）
    int skillPointGainCD; // 回复技能点的CD（单位：帧）
    int maxSkillPointGainCD; // 回复技能点的总CD（单位：帧）
    int hasBuff[BuffType::BUFF_TYPE_CNT]; // 当前玩家带有的Buff的列表
    GamePlayer *opponent; // 对手

    // methods
    virtual void skill() = 0;
    virtual void updateInGame();
    virtual void collides(GameObject *obj);
    virtual void takeDamage(int damage);
    void magnet();

protected:
    std::list<GameObject *> *gameObjects;

};

class LovingMan: public GamePlayer
{
public:
    LovingMan(int x, int y,
              const QPixmap *pixmap_,
              QGraphicsScene *scene_,
              GamePlayer *opponent_,
              std::list<GameObject *> *gameObjects_):
        GamePlayer(x, y, pixmap_, scene_, opponent_, gameObjects_)
        {playerType = LOVING_MAN;}
private:
    virtual void skill();
};

class SantaClaus: public GamePlayer
{
public:
    SantaClaus(int x, int y,
               const QPixmap *pixmap_,
               QGraphicsScene *scene_,
               GamePlayer *opponent_,
               std::list<GameObject *> *gameObjects_):
        GamePlayer(x, y, pixmap_, scene_, opponent_, gameObjects_)
    {playerType = SANTA_CLAUS;}
private:
    virtual void skill();
};

class AngryBrother: public GamePlayer
{
public:
    AngryBrother(int x, int y,
                 const QPixmap *pixmap_,
                 QGraphicsScene *scene_,
                 GamePlayer *opponent_,
                 std::list<GameObject *> *gameObjects_):
        GamePlayer(x, y, pixmap_, scene_, opponent_, gameObjects_)
    {playerType = ANGRY_BROTHER;}
private:
    virtual void skill();
};

class GuoShen:  public GamePlayer
{
public:
    GuoShen(int x, int y,
            const QPixmap *pixmap_,
            QGraphicsScene *scene_,
            GamePlayer *opponent_,
            std::list<GameObject *> *gameObjects_):
        GamePlayer(x, y, pixmap_, scene_, opponent_, gameObjects_)
    {playerType = GUO_SHEN;}
private:
    virtual void skill();
};

#endif // !PLAYER_H
