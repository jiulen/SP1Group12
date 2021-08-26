#pragma once
#include "Entity.h"
class Guard :
    public Entity
{
public:
    Guard();
    ~Guard();
    void move(int);
private:
    int patrol_dir;
};

