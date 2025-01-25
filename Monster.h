#ifndef MONSTER_H
#define MONSTER_H
#include "Entity.h"
#include "Player.h"

// abstract
class Monster :public Entity {
protected:
    Player *fighting_who = nullptr; // who is the entity fighting at the moment
public:
    using Entity::Entity; // constructors from Entity
    virtual ~Monster();
    int attacked(); // all monsters are attacked the same way
    void set_fighting_who(Player* fighting_who);


};



#endif //MONSTER_H
