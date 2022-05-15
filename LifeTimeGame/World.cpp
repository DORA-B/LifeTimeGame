#include "World.h"


World::World(int w, int h, int d)
{
	width = w;
	height = h;
	depth = d;
	grid = (short*)malloc((width + 2) * (height + 2) * (depth + 2) * sizeof(short));
	new_grid = (short*)malloc((width + 2) * (height + 2) * (depth + 2) * sizeof(short));

	for (unsigned int i = 0; i < (width + 2) * (height + 2) * (depth + 2); i++)
	{
		grid[i] = short(0);
		new_grid[i] = short(0);
	}
}

World::~World() {
	free(grid); 
	free(new_grid);
}

void World::setNewLife(int x, int y, int z, int val)
{
	new_grid[y + x * (width + 2) + z * (width + 2) * (height + 2)] = val;
}

void World::swapGrids()
{
	std::swap(grid, new_grid);
}

int World::getNeighbors(int x, int y, int z)
{
	int count = 0;
	//周围共有26个

	count += grid[(y + 1) + x * (width + 2) + z * (width + 2) * (height + 2)];
	count += grid[(y + 1) + x * (width + 2) + (z + 1) * (width + 2) * (height + 2)];
	count += grid[(y + 1) + x * (width + 2) + (z - 1) * (width + 2) * (height + 2)];

	count += grid[(y + 1) + (x + 1) * (width + 2) + (z + 1) * (width + 2) * (height + 2)];
	count += grid[(y + 1) + (x + 1) * (width + 2) + (z) * (width + 2) * (height + 2)];
	count += grid[(y + 1) + (x + 1) * (width + 2) + (z - 1) * (width + 2) * (height + 2)];

	count += grid[(y + 1) + (x - 1) * (width + 2) + z * (width + 2) * (height + 2)];
	count += grid[(y + 1) + (x - 1) * (width + 2) + (z + 1) * (width + 2) * (height + 2)];
	count += grid[(y + 1) + (x - 1) * (width + 2) + (z - 1) * (width + 2) * (height + 2)];
	//
	count += grid[(y - 1) + x * (width + 2) + z * (width + 2) * (height + 2)];
	count += grid[(y - 1) + x * (width + 2) + (z + 1) * (width + 2) * (height + 2)];
	count += grid[(y - 1) + x * (width + 2) + (z - 1) * (width + 2) * (height + 2)];

	count += grid[(y - 1) + (x + 1) * (width + 2) + (z + 1) * (width + 2) * (height + 2)];
	count += grid[(y - 1) + (x + 1) * (width + 2) + (z) * (width + 2) * (height + 2)];
	count += grid[(y - 1) + (x + 1) * (width + 2) + (z - 1) * (width + 2) * (height + 2)];

	count += grid[(y - 1) + (x - 1) * (width + 2) + z * (width + 2) * (height + 2)];
	count += grid[(y - 1) + (x - 1) * (width + 2) + (z + 1) * (width + 2) * (height + 2)];
	count += grid[(y - 1) + (x - 1) * (width + 2) + (z - 1) * (width + 2) * (height + 2)];
	//
	count += grid[(y)+x * (width + 2) + (z + 1) * (width + 2) * (height + 2)];
	count += grid[(y)+x * (width + 2) + (z - 1) * (width + 2) * (height + 2)];

	count += grid[(y)+(x + 1) * (width + 2) + (z + 1) * (width + 2) * (height + 2)];
	count += grid[(y)+(x + 1) * (width + 2) + (z) * (width + 2) * (height + 2)];
	count += grid[(y)+(x + 1) * (width + 2) + (z - 1) * (width + 2) * (height + 2)];

	count += grid[(y)+(x - 1) * (width + 2) + z * (width + 2) * (height + 2)];
	count += grid[(y)+(x - 1) * (width + 2) + (z + 1) * (width + 2) * (height + 2)];
	count += grid[(y)+(x - 1) * (width + 2) + (z - 1) * (width + 2) * (height + 2)];

	return count;
}

int World::getLifeform(int x, int y, int z)
{
	return grid[y + x * (width + 2) + z * (width + 2) * (height + 2)];
}

void World::setLife(int x, int y, int z, int val)
{
	grid[y + x * (width + 2) + z * (width + 2) * (height + 2)] = val;
}

