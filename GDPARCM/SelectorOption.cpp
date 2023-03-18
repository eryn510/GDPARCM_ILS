#include "SelectorOption.h"
#include <iostream>
#include "TextureManager.h"

SelectorOption::SelectorOption(std::string name) : AObject(name)
{
	std::cout << "Declared as " << name << "\n";
}

void SelectorOption::initialize()
{

}

void SelectorOption::initialize(std::string OptionText, sf::Vector2u textureSize, sf::Vector2f posMove)
{
	//assign texture
	this->sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("Selector", 0);
	this->sprite->setTexture(*texture);
	this->sprite->setTextureRect(sf::IntRect(0, 0, texture->getSize().x, texture->getSize().y));

	this->sprite->setOrigin(texture->getSize().x / 2, texture->getSize().y / 2);
	this->setPosition((textureSize.x / 2) + posMove.x, (textureSize.y / 2) + posMove.y);

	this->text = new sf::Text();
	sf::Font* font = new sf::Font();

	font->loadFromFile("Media/Sansation.ttf");

	this->text->setFont(*font);
	this->text->setString(OptionText);
	this->text->setCharacterSize(36);
	this->text->setFillColor(sf::Color::Black);
	this->text->setOrigin(this->text->findCharacterPos(this->text->getString().getSize() / 2).x, 
		this->text->getCharacterSize() / 2);
	this->text->setPosition((textureSize.x / 2) + posMove.x, (textureSize.y / 2) + posMove.y);

	this->isCurrentlySelected = false;
}

void SelectorOption::processInput(sf::Event event)
{
}

void SelectorOption::Update(sf::Time deltaTime)
{
}

void SelectorOption::Draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates)
{
	if (this->getParent() != nullptr && this->getParent()->isEnabled())
	{
		if (isCurrentlySelected)
			targetWindow->draw(*this->getSprite(), renderStates);

		targetWindow->draw(*this->text, renderStates);
	}
	
}
