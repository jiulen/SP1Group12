#include "Golem.h"

Golem::Golem() {
	set_hp(20);
	set_dmg(5);
	set_def(1);
}
//has 20 health and 1 def, so with sword, deals 2 dmg, 10 hits

Golem::~Golem() {

}

void Golem::move() {
	//when player within 10 units, charge at player at 4 units/90 frames, does 5 damage, wait 3 seconds and redo, maybe 3x3 aoe charge
}