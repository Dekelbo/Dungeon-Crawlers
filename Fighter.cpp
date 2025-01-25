
#include "Fighter.h"

Fighter::Fighter(int max_life, int damage) : Player("Fighter", max_life, damage){}
Fighter::~Fighter() {
}

int Fighter::attacked() {
    if(this->special_attack_wait == 1) {
        return 0; // special power is on, deals with 0 damage
    }
    //special power is off
    *this -= *(this->fighting_who);
     return this->fighting_who->getDamage();

}

int Fighter::attack() {
    this->special_attack_wait = (this->special_attack_wait + 1) % WAITING_TIME; // update the turns - range 0-4
    return this->fighting_who->attacked();
}
