#pragma once
#include "Position.h"

class Entity {
public:
	Entity();
	~Entity();
	Position EntityPos;
	virtual void move();
	int Random_Integer(); //what this for?

	int get_hp(void);
	void set_hp(int);

	int get_dmg(void);
	void set_dmg(int);

	int get_def(void);
	void set_def(int);

	int get_posX(void);
	int get_posY(void);

	

protected:
	
	int hp, dmg, def;

};