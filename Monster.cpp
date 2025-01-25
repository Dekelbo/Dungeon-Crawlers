
#include "Monster.h"

Monster:: ~Monster() {}

int Monster::attacked() {
    *this -= *(this->fighting_who);
    return this->fighting_who->getDamage();
}
