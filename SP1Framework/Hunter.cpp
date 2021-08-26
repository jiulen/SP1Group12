#include "Hunter.h"
Hunter::Hunter() {
	hp = 1;
	dmg = 2;
	def = 0;
	face = "..";
    colour = 0x94;
}
Hunter::~Hunter() {

}
void Hunter::move(int dir) {
    switch (dir) {
    case 0: // up
        EntityPos.setPosition(get_posX(), get_posY() - 1); break;
    case 1: // down
        EntityPos.setPosition(get_posX(), get_posY() + 1); break;
    case 2: // left
        EntityPos.setPosition(get_posX() - 2, get_posY()); break;
    case 3: // right
        EntityPos.setPosition(get_posX() + 2, get_posY()); break;
    }
}