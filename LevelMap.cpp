#include "LevelMap.h"
#include <iostream>
using namespace::std;
/*
-----------------------------------------------------
0 = empty 
1 = tiled area of map
-----------------------------------------------------
*/

LevelMap::LevelMap(int map[MAP_HEIGHT][MAP_WIDTH])
{
	//allocate memory for the map
	mMap = new int* [MAP_HEIGHT];

	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		mMap[i] = new int[MAP_WIDTH];
	}

	//populate the map array
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		for (unsigned int j = 0; j < MAP_WIDTH; j++)
		{
			mMap[i][j] = map[i][j];
		}
	}
}

LevelMap::~LevelMap()
{
	//delete the map created 
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		delete[] mMap[i];
	}
	delete[] mMap;
}

int LevelMap::GetTileAt(unsigned int h, unsigned int w)
{
	//return each tile in the array
	if (h < MAP_HEIGHT && w < MAP_WIDTH)
	{
		return mMap[h][w];
	}

	return 0;
}

void LevelMap::ChangeTileAt(unsigned int row, unsigned int col, unsigned int newVal)
{
	mMap[row][col] = newVal;
}