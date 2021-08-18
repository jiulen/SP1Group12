#include "Slime.h"

int Slime::slime_kills = 0;

Slime::Slime() {
	

	set_hp(1);
	set_dmg(2);
	set_def(0);
}

Slime::~Slime() {
	slime_kills++;
}

void Slime::move() {

}