#include "StatusBar.h"
#include <iostream>
#include "TextureManager.h"

StatusBar::StatusBar(std::string name, Character character) : AObject(name), character(character)
{
	std::cout << "Declared as " << name << "\n";

	//assign texture
	this->sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("StatusBar", 0);
	this->sprite->setTexture(*texture);
	this->sprite->setTextureRect(sf::IntRect(0, 0, texture->getSize().x, texture->getSize().y));
	this->sprite->setOrigin(texture->getSize().x / 2, texture->getSize().y / 2);
	sf::Vector2u textureSize = this->sprite->getTexture()->getSize();

	UIDisplay* image = nullptr;

	if (character == ESTELLE)
		image = new UIDisplay("EstelleImage", TextureManager::getInstance()->getFromTextureMap("EstelleUINormal", 0));
	else if (character == JOSHUA)
		image = new UIDisplay("JoshuaImage", TextureManager::getInstance()->getFromTextureMap("JoshuaUINormal", 0));

	this->attachChild(image);
	image->setScale(0.6, 0.6);
	image->setPosition(-(textureSize.x / 2.0f) + (image->getSprite()->getTexture()->getSize().x / 2.0f), (textureSize.y / 2.0f) - 65);

	UIDisplay* HPIcon = new UIDisplay("HPIcon", TextureManager::getInstance()->getFromTextureMap("HP", 0));
	this->attachChild(HPIcon);
	HPIcon->setScale(0.35, 0.35);
	HPIcon->setPosition((texture->getSize().x / 2) - 30, (texture->getSize().y / 2) - 40);

	UIDisplay* MPIcon = new UIDisplay("MPIcon", TextureManager::getInstance()->getFromTextureMap("MP", 0));
	this->attachChild(MPIcon);
	MPIcon->setScale(0.35, 0.35);
	MPIcon->setPosition((texture->getSize().x / 2) - 30, (texture->getSize().y / 2));
}

void StatusBar::initialize()
{
	
}

void StatusBar::Update(sf::Time deltaTime)
{
}
