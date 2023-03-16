#include "UIDisplay.h"
#include "TextureManager.h"
#include <iostream>

UIDisplay::UIDisplay(std::string name, sf::Texture* tex, float width, float height) : AObject(name)
{
	std::cout << "Declared as " << name << "\n";

	//assign texture
	this->sprite = new sf::Sprite();
	sf::Texture* texture = tex;
	this->sprite->setTexture(*texture);
	this->sprite->setTextureRect(sf::IntRect(0, 0, texture->getSize().x, texture->getSize().y));

	if (width != 0 && height != 0)
		this->sprite->setScale(width / this->sprite->getTexture()->getSize().x, height / this->sprite->getTexture()->getSize().y);


	this->sprite->setOrigin(this->sprite->getTexture()->getSize().x / 2, this->sprite->getTexture()->getSize().y / 2);
}

void UIDisplay::initialize()
{

}

void UIDisplay::Update(sf::Time deltaTime)
{
}

sf::Sprite* UIDisplay::getSprite()
{
	return this->sprite;
}
