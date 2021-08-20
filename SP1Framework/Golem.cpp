#include "Golem.h"

Golem::Golem() {
	hp = 20;
	dmg = 5;
	def = 1;
}
//has 20 health and 1 def, so with sword, deals 2 dmg, 10 hits

Golem::~Golem() {

}

void Golem::move() {
	//when player within 10 units, charge at player at 4 units/90 frames, does 4 damage, wait 3 seconds and redo, deals damage in a 1 block radius around itself
}