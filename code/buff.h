#ifndef BUFF_H
#define BUFF_H


class Buff
{
public:
    enum BuffType{
        SPEED, FREEZE, MAGNET, RAGE, BUFF_TYPE_CNT
    } type;
    int remainTime;

    Buff(BuffType type, int time);
};

#endif // BUFF_H
