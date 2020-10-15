#ifndef _LEVEL1_MAP_H
#define _LEVEL1_MAP_H

#include "Constants.h"

class LevelMap
{
public:
	//initialize the levelmap with an array, passed the height (col) and row (width)
	LevelMap(int map[MAP_HEIGHT][MAP_WIDTH]);
	~LevelMap();

	//get the position of the tile 
	int GetTileAt(unsigned int h, unsigned int w);
	//allows us to change a destroyed box's value
	void ChangeTileAt(unsigned int row, unsigned int column, unsigned int newVal);
private:
	int** mMap;
};
#endif // !_LEVEL1_MAP_H