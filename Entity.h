#ifndef ENTITY_H
#define ENTITY_H
#include <ostream>


class Entity {
    char* name;
    int max_life;
    int current_life;
    int damage;

public:

    //constructor
    Entity(const char* name, int max_life, int damage);
    //copy constructor
    Entity(const Entity& other);
    //destructor
    virtual ~Entity();

    void setDamage(int damage);
    int getDamage() const;
    int getCurrentLife() const;
    char *getName() const;

    virtual void attack() = 0; // pure virtual - no instance of Entity

    //current_life+=num
    void operator+= (int num);
    //current_life-= other.damage
    void operator-= (const Entity& otherEntity);
    //print
    friend std::ostream& operator<<(std::ostream& os, const Entity& other);
    //comp by current_life * damage
    bool operator> (const Entity& otherEntity) const;
    //comp by current_life * damage
    bool operator== (const Entity& otherEntity) const;
};

#endif //ENTITY_H
