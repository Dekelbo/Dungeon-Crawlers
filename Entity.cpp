#include "Entity.h"
#include <cstring>
using namespace std;

//constructor
Entity::Entity(const char* name, int max_life, int damage) {

    this->name = strdup(name);
    this->max_life = max_life;
    this->current_life = max_life; //initialize curr_life with max_life
    this->damage = damage;
}
//copy constructor
Entity::Entity(const Entity& other) {
    this->name=strdup(other.name);
    this->max_life= other.max_life;
    this->current_life = other.current_life;
    this->damage = other.damage;
}

//destructor
Entity::~Entity() {
    free(this->name);
}

void Entity::setDamage(int damage) {
    this->damage = damage;
}


int Entity::getDamage() const {
    return this->damage;
}

// Getter for life
int Entity::getCurrentLife() const {
    return this->current_life;
}

// Getter for name
char *Entity::getName() const {
    return this->name;
}

//current_life+=num
void Entity::operator+= (int num) {
    this->current_life = this->current_life + num;

    // max
    if(this->current_life > this->max_life) {
        this->current_life = this->max_life;
    }
}
//current_life-= other.damage
void Entity::operator-= (const Entity& otherEntity){
    this->current_life = this->current_life - otherEntity.damage;

    // min 0
    if(this->current_life < 0) {
        this->current_life = 0;
    }
}
//print
std::ostream& operator<<(std::ostream& os, const Entity& other) {
    os << other.name << " (" << other.current_life << "/" << other.max_life << ") - " << other.damage;
    return os;
}
//comp by current_life * damage
bool Entity::operator> (const Entity& otherEntity) const {
    return (this->current_life * this->damage) > (otherEntity.current_life * otherEntity.damage);

}
//comp by current_life * damage
bool Entity::operator== (const Entity& otherEntity) const {
    return (this->current_life * this->damage) == (otherEntity.current_life * otherEntity.damage);
}
