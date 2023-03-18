#include "UIBox.h"
#include "TextureManager.h"
#include <iostream>

UIBox::UIBox(std::string name) : AObject(name)
{
	std::cout << "Declared as " << name << "\n";

	//assign texture
	this->sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("UIBox", 0);
	this->sprite->setTexture(*texture);
	this->sprite->setTextureRect(sf::IntRect(0, 0, texture->getSize().x, texture->getSize().y));
	this->sprite->setOrigin(this->sprite->getTexture()->getSize().x / 2, this->sprite->getTexture()->getSize().y / 2);
}

void UIBox::initialize()
{
}

void UIBox::processInput(sf::Event event)
{
}

void UIBox::Update(sf::Time deltaTime)
{
}
