#include "ProgressBar.h"
#include <iostream>

ProgressBar::ProgressBar(std::string name) : AObject(name)
{
	std::cout << "Declared as " << name << "\n";

	this->back = new sf::RectangleShape();
	this->inner = new sf::RectangleShape();
}

void ProgressBar::initialize()
{
}

void ProgressBar::initialize(float x, float y, float width, float height, sf::Color inner_color, unsigned character_size, sf::Font* font)
{
	this->maxWidth = width;

	this->back->setSize(sf::Vector2f(width, height));
	this->back->setFillColor(sf::Color(50, 50, 50, 200));
	this->back->setPosition(x, y);

	this->inner->setSize(sf::Vector2f(width, height));
	this->inner->setFillColor(inner_color);
	this->inner->setPosition(this->back->getPosition());

	if (font)
	{
		this->text.setFont(*font);
		this->text.setCharacterSize(25);
		this->text.setPosition(
			this->inner->getPosition().x,
			this->inner->getPosition().y
		);
	}
}

void ProgressBar::Update(sf::Time deltaTime)
{
}

void ProgressBar::processInput(sf::Event event)
{
}

void ProgressBar::Draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates)
{
	AObject::Draw(targetWindow, renderStates);

	targetWindow->draw(*this->back, renderStates);
	targetWindow->draw(*this->inner, renderStates);
	targetWindow->draw(this->text, renderStates);

}

void ProgressBar::setPosition(float x, float y)
{
	this->posX = x;
	this->posY = y;

	this->back->setPosition(x, y);
	this->inner->setPosition(x, y);
}

void ProgressBar::setScale(float x, float y)
{
	this->scaleX = x;
	this->scaleY = y;

	this->back->setScale(x, y);
	this->inner->setScale(x, y);
}

sf::Vector2f ProgressBar::getPosition()
{
	return this->back->getPosition();
}

sf::Vector2f ProgressBar::getScale()
{
	return this->back->getScale();
}

void ProgressBar::setFill(float percentage)
{
	this->inner->setSize(sf::Vector2f(this->maxWidth * percentage, this->inner->getSize().y));
	this->currentFill = percentage;
}
