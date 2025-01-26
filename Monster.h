#ifndef MONSTER_H
#define MONSTER_H
#include "Player.h"

// Forward declaration
class Player;

// abstract
class Monster :public Entity {
protected:
    Player *fighting_who = nullptr; // who is the monster fighting at the moment
public:
    Monster(const char* name, int max_life, int damage) : Entity(name, max_life, damage) {} // constructors from Entity
    virtual ~Monster();
    int attacked(); // all monsters are attacked the same way
    void set_fighting_who(Player* fighting_who);


};



#endif //MONSTER_H
