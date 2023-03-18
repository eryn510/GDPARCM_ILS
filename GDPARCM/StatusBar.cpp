#include "StatusBar.h"
#include <iostream>
#include "TextureManager.h"
#include "ProgressBar.h"
#include "CombatLoop.h"

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

	UIDisplay* SPIcon = new UIDisplay("SPIcon", TextureManager::getInstance()->getFromTextureMap("SP", 0));
	this->attachChild(SPIcon);
	SPIcon->setScale(0.35, 0.35);
	SPIcon->setPosition((texture->getSize().x / 2) - 30, (texture->getSize().y / 2) + 40);

	ProgressBar* HPProgress = new ProgressBar("HPProgress");
	this->attachChild(HPProgress);
	HPProgress->initialize((texture->getSize().x / 2), (texture->getSize().y / 2), 175, 15, sf::Color::Red, 0);
	HPProgress->setPosition((texture->getSize().x / 2), (texture->getSize().y / 2) - 47.5);

	ProgressBar* MPProgress = new ProgressBar("MPProgress");
	this->attachChild(MPProgress);
	MPProgress->initialize((texture->getSize().x / 2), (texture->getSize().y / 2), 175, 15, sf::Color::Blue, 0);
	MPProgress->setPosition((texture->getSize().x / 2), (texture->getSize().y / 2) - 7.5);

	ProgressBar* SPProgress = new ProgressBar("SPProgress");
	this->attachChild(SPProgress);
	SPProgress->initialize((texture->getSize().x / 2), (texture->getSize().y / 2), 175, 15, sf::Color::Green, 0);
	SPProgress->setPosition((texture->getSize().x / 2), (texture->getSize().y / 2) + 32.5);
	this->spBar = SPProgress;


}

void StatusBar::initialize()
{
	
}

void StatusBar::processInput(sf::Event event)
{
}

void StatusBar::Update(sf::Time deltaTime)
{
	this->spBar->setFill(CombatLoop::getInstance()->load->currentFill);
}
