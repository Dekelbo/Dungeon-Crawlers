
#include "Dragon.h"

Dragon::Dragon(int max_life, int damage) : Monster("Dragon", max_life, damage){}
Dragon::~Dragon() {
}

int Dragon::attack() {
    return this->fighting_who->attackedByDragon();
}