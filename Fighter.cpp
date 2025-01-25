
#include "Fighter.h"

Fighter::Fighter(int max_life, int damage) : Player("Fighter", max_life, damage){}
Fighter::~Fighter() {
}

int Fighter::attackedByDragon() {
    if(this->special_attack_wait == 1) {
        return 0; // special power is on, deals with 0 damage
    }
    //special power is off
    int actual_damage = (this->fighting_who->getDamage() + 1) / 2; // dragon deals half damage to fighter
	return (*this -= actual_damage);
}

int Fighter::attackedByGoblin() {
    if(this->special_attack_wait == 1) {
        return 0; // special power is on, deals with 0 damage
    }
    //special power is off
    int actual_damage = this->fighting_who->getDamage() * 2; // goblin deals double damage to fighter
	return (*this -= actual_damage);
}

int Fighter::attack() {
    this->special_attack_wait = (this->special_attack_wait + 1) % WAITING_TIME; // update the turns - range 0-4
    return this->fighting_who->attacked();
}
