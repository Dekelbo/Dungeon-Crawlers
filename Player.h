
#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include "Monster.h"

#define WAITING_TIME 5 // can use special power once in 5 turns

// abstract
class Player : public Entity {
protected:
    Monster *fighting_who = nullptr; // who is the entity fighting at the moment
    int special_attack_wait = 0; // 0  - power is off and turns it on,  1 - can use the power because power is on, 2-4  power is off)

public:
    Player(const char* name, int max_life, int damage); // calls entity's constructor
    virtual ~Player();
    virtual int attackedByDragon() = 0; // player is attacked by a dragon - pure virtual
    virtual int attackedByGoblin() = 0; // player is attacked by a goblin - pure virtual
    virtual int attack() = 0; // player attacks - pure virtual

};



#endif //PLAYER_H
