#ifndef MONSTER_H
#define MONSTER_H
#include "Entity.h"

// abstract
class Monster :public Entity {
public:
    using Entity::Entity; // constructors from Entity
    virtual ~Monster();

};



#endif //MONSTER_H
