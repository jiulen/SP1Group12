#include "Golem.h"

Golem::Golem() {
	hp = 20;
	dmg = 5;
	def = 1;
}
//has 20 health and 1 def, so with sword, deals 2 dmg, 10 hits

Golem::~Golem() {

}

void Golem::move(int direction) {
    switch (direction) {
    case 0: // up
        EntityPos.setPosition(get_posX(), get_posY() - 1); break;
    case 1: // down
        EntityPos.setPosition(get_posX(), get_posY() + 1); break;
    case 2: // left
        EntityPos.setPosition(get_posX() - 2, get_posY()); break;
    case 3:
        EntityPos.setPosition(get_posX() + 2, get_posY()); break;
    }
}