#pragma once
#include "Entity.h"
class Slime :public Entity {
public:
	Slime();
	~Slime();
	void move();
	void slimespawn();
private:
	static int slime_kills;
};