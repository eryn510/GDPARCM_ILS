#pragma once
#include "Tile.h"
#include "ObjectManager.h"

class IsometricMap
{
public:
	IsometricMap(int x, int y);
	~IsometricMap();

	void initializeMap();
	void recursiveGenerate(int xBounds, int yBounds, int recursionCount);

protected:
	int maxX, maxY;
};

