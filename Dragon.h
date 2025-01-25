
#ifndef DRAGON_H
#define DRAGON_H
#include "Monster.h"


class Dragon : public Monster {

public:
    Dragon(int max_life, int damage);
    virtual ~Dragon();
    virtual void attack();
};



#endif //DRAGON_H
