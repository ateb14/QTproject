#include "buff.h"

BuffSet::BuffSet()
{
    this->buffSet = 0;
}

void BuffSet::addBuff(Buff buff)
{
    buffSet |= buff;
}

bool BuffSet::contains(Buff buff)
{
    return buffSet&buff;
}
