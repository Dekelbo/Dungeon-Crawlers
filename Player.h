
#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"


class Player : public Entity {


public:
    Player(const char* name, int max_life, int damage);
    virtual ~Player();
    virtual int special_power() = 0;

};



#endif //PLAYER_H
