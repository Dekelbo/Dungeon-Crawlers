#ifndef GOBLIN_H
#define GOBLIN_H
#include "Monster.h"


class Goblin : public Monster {

public:
    Goblin(int max_life, int damage);
    virtual ~Goblin();
    virtual void attack();

};



#endif //GOBLIN_H
