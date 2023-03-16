#pragma once
#include "SFML/Graphics.hpp"
#include "IsometricMapSprite.h"
#include <list>

class IsometricMapNode
{
public:
	IsometricMapNode();
	~IsometricMapNode();

	void drawFloors(sf::RenderWindow* win, sf::Color& color);
	void drawObjects(sf::RenderWindow* win, sf::Color& color);
	void drawWindow(sf::RenderWindow* win, sf::Color& color);
	void drawRoofs(sf::RenderWindow* win, sf::Color& color);


	void addFloors(IsometricMapSprite* s);
	void addWall(IsometricMapSprite* s);
	void addRoofs(IsometricMapSprite* s);

	void insertSprite(IsometricMapSprite* s);
	void removeSprite(IsometricMapSprite* s);
	void clear();

protected:
	std::list<IsometricMapSprite*> m_floors, m_walls, m_roofs, m_objects;
};

