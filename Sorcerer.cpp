
#include "Sorcerer.h"
Sorcerer::Sorcerer(int max_life, int damage) : Player("Sorcerer", max_life, damage){}
Sorcerer::~Sorcerer() {
}

int Sorcerer::attacked() {
	*this -= *(this->fighting_who);
	return this->fighting_who->getDamage();
}

int Sorcerer::attack() {
    this->special_attack_wait = (this->special_attack_wait + 1) % WAITING_TIME; // update the turns - range 0-4
    if (special_attack_wait == 1) {
		this->damage *= 2; // special power is on, double demage
	}
	int demage_dealt = this->fighting_who->attacked();
	if (special_attack_wait == 1) {
		this->damage /= 2; // already used special power, back to normal demage
	}
	return demage_dealt;
}