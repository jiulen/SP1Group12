#include "Slime.h"

int Slime::slime_kills = 0;		//shows up as number of enemies killed at the end

Slime::Slime() {
	hp = 1;
	dmg = 2;
	def = 0;
}

Slime::~Slime() {
	slime_kills++;
}

void Slime::move(int direction) {
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