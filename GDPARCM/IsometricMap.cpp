#include "IsometricMap.h"

IsometricMap::IsometricMap(int x, int y) : maxX(x), maxY(y)
{
}

IsometricMap::~IsometricMap()
{
}

void IsometricMap::initializeMap()
{
    int xCounter;
    int yCounter = -maxY;
    int recursionCount = 0;
    
    for (xCounter = maxX; xCounter > 0; xCounter--)
    {
        recursiveGenerate(xCounter, yCounter, recursionCount);
        yCounter++;
        recursionCount++;
    }
    
}

void IsometricMap::recursiveGenerate(int xBounds, int yBounds, int recursionCount)
{
    Tile* tile;

    int y = yBounds;
    for (int x = 0 - recursionCount; x < xBounds; x++)
    {
        tile = new Tile("tile");
        tile->setScale(3, 3);
        tile->setPosition(x * 8 * tile->getScale().x, y * 8 * tile->getScale().y);
        ObjectManager::getInstance()->addObject(tile);
        y++;
    }
}
