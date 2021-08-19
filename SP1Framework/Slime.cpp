#include "Slime.h"

int Slime::slime_kills = 0;		//shows up as number of enemies killed at the end

Slime::Slime() {
	

	set_hp(1);
	set_dmg(2);
	set_def(0);
}

Slime::~Slime() {
	slime_kills++;
}

void Slime::move() {				//1 2 3 4 for up down left right
	int randint = Random_Integer();
	if (randint == 1) {

	}
	else if (randint == 2) {

	}
	else if (randint == 3) {

	}
	else if (randint == 4) {

	}


}