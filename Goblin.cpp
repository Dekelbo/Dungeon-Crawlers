
#include "Goblin.h"

Goblin::Goblin(int max_life, int damage) : Monster("Goblin", max_life, damage){}
Goblin::~Goblin() {
}

int Goblin::attack() {
    return this->fighting_who->attackedByGoblin();
}