
#include "Monster.h"

Monster:: ~Monster() {}

int Monster::attacked() {
    *this -= *(this->fighting_who);
    return this->fighting_who->getDamage();
}

void Monster::set_fighting_who(Player* fighting_who) {
    this->fighting_who = fighting_who;
}