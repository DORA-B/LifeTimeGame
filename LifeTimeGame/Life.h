#include "World.h"


#ifndef LIFE_H
#define LIFE_H

class Life : public World
{
public:
	Life(int x, int y, int z) : World(x, y, z) {}
	void update();
};

#endif
