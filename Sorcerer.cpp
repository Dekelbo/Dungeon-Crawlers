
#include "Sorcerer.h"
Sorcerer::Sorcerer(int max_life, int damage) : Player("Sorcerer", max_life, damage){}
Sorcerer::~Sorcerer() {
}

int Sorcerer::attackedByDragon() {
	int actual_damage = this->fighting_who->getDamage() * 2; // dragon deals double damage to sorcerer
	return (*this -= actual_damage);
}

int Sorcerer::attackedByGoblin() {
	int actual_damage = (this->fighting_who->getDamage() + 1) / 2; // goblin deals half damage to sorcerer
	return (*this -= actual_damage);
}

int Sorcerer::attack() {
    this->updateTurn(); // update the turns - range 0-4
    if (special_attack_wait == 1) {
		this->damage *= 2; // special power is on, double damage
	}
	int damage_dealt = this->fighting_who->attacked();
	if (special_attack_wait == 1) {
		this->damage /= 2; // already used special power, back to normal damage
	}
	return damage_dealt;
}