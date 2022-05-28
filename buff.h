#ifndef GAMEBUFF_H
#define GAMEBUFF_H

enum Buff{
    SPEED_DOWN = 1<<0,
    SPEED_UP = 1<<1,
    SHOOT_SPEED_UP = 1<<2,
    SHOOT_SPEED_DOWN = 1<<3
};

class BuffSet
{
private:
    long long buffSet;
public:
    BuffSet();
    void addBuff(Buff buff);
    bool contains(Buff buff);
};

#endif // GAMEBUFF_H
