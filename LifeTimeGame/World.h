#include <iostream>
using std::cout;
using std::malloc;
using std::endl;

#ifndef WORLD_H
#define WORLD_H

class World
{
protected:
	short* grid;
	short* new_grid;
	unsigned int width;
	unsigned int height;
	unsigned int depth;

	void setNewLife(int x, int y, int z, int val);
	void swapGrids();

public:
	World(int, int, int);
	~World();
	int getLifeform(int x, int y, int z);
	int getNeighbors(int, int, int);
	void setLife(int x, int y, int z, int val);
	virtual void update() { } //±ªºÃ≥–£¨ π”√virtual
};

#endif
