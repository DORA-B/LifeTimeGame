#include "Life.h"


void Life::update()
{
	for (unsigned int i = 1; i <= height; i++)
	{
		for (unsigned int j = 1; j <= width; j++)
		{
			for (unsigned int k = 1; k <= depth; k++)
			{
				int neighbor = getNeighbors(i, j, k);
				if (neighbor == 5)
				{
					setNewLife(i, j, k, 1);
				}
				else if (neighbor < 3)
				{
					setNewLife(i, j, k, 0);
				}
				else if (neighbor > 5)
				{
					setNewLife(i, j, k, 0);
				}
				else if ((neighbor == 4) || (neighbor == 5))
				{
					setNewLife(i, j, k, getLifeform(i, j, k));
				}
			}
		}
	}
	swapGrids();
}

