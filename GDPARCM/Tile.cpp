#include "Tile.h"
#include "TextureManager.h"
#include <iostream>

Tile::Tile(std::string name) : AIsometricObject(name)
{
	std::cout << "Declared as " << name << "\n";

	//assign texture
	this->sprite = new IsometricMapSprite();
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("DirtTile", 0);
	this->sprite->setTexture(*texture);
}

void Tile::initialize()
{
}

void Tile::Update(sf::Time deltaTime)
{
}
