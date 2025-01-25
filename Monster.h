#ifndef MONSTER_H
#define MONSTER_H
#include "Entity.h"

// abstract
class Monster :public Entity {
public:
    using Entity::Entity; // constructors from Entity
    virtual ~Monster();
    virtual int attacked(); // all monsters are attacked the same way

};



#endif //MONSTER_H
