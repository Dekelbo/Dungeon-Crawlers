
#ifndef SORCERER_H
#define SORCERER_H
#include "Player.h"


class Sorcerer : public Player {

public:
    Sorcerer(int max_life, int damage);
    virtual ~Sorcerer();
    virtual int attacked();
    virtual int attack();
};



#endif //SORCERER_H
