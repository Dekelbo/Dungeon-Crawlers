#ifndef MONSTER_H
#define MONSTER_H
#include "Entity.h"


class Monster :public Entity {
public:
    using Entity::Entity; // constructors from Entity
    virtual ~Monster();

};



#endif //MONSTER_H
