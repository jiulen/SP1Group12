#pragma once
#include "Position.h"

class Entity {
public:
	Entity();
	~Entity();

	virtual void move();
	int Random_Integer(); //what this for?

	int get_hp(void);
	void set_hp(int);

	int get_dmg(void);
	void set_dmg(int);

	int get_def(void);
	void set_def(int);

protected:
	Position EntityPos;
	int hp, dmg, def;

};