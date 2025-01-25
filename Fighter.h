#ifndef FIGHTER_H
#define FIGHTER_H
#include "Player.h"


class Fighter : public Player {

public:
    Fighter(int max_life, int damage);
    virtual ~Fighter();
    virtual int attacked();
    virtual int attack();

};



#endif //FIGHTER_H
