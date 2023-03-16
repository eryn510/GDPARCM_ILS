#include "AIsometricObject.h"
#include <iostream>
#include "MathUtils.h"

AIsometricObject::AIsometricObject(std::string name) : AObject(name)
{

}

AIsometricObject::~AIsometricObject()
{
	if (this->sprite != NULL) {
		delete this->sprite;
	}
}

std::string AIsometricObject::getName()
{
	return name;
}

void AIsometricObject::Draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates)
{
	if (this->sprite != NULL) {
		// Set view
		sf::View view = targetWindow->getView();
		// Reverse project center
		sf::Vector2f center = MathUtils::WorldToScreen(sf::Vector2f(0, 0));
		view.setCenter(center);
		targetWindow->setView(view);

		// Reverse-project top-left corner
		sf::Vector2f viewsize = view.getSize();
		sf::Vector2f topleft = MathUtils::ScreenToWorld(sf::Vector2f(center.x - viewsize.x / 2.0f, center.y - viewsize.y / 2.0f));

		this->sprite->setWorldPosition(this->posX, this->posY);
		this->sprite->setScale(this->scaleX, this->scaleY);
		targetWindow->draw(*this->sprite);
	}

	
}

void AIsometricObject::Update(sf::Time deltaTime)
{
	// Add Implementation here
}

void AIsometricObject::setPosition(float x, float y)
{
	this->posX = x;
	this->posY = y;

	if (this->sprite != nullptr)
	{
		this->sprite->setWorldPosition(this->posX, this->posY);
	}
}

void AIsometricObject::setPosition(sf::Vector2f pos)
{
	this->posX = pos.x;
	this->posY = pos.y;

	if (this->sprite != nullptr)
	{
		this->sprite->setWorldPosition(this->posX, this->posY);
	}
}

void AIsometricObject::setCenter(float x, float y)
{
	this->center = sf::Vector2f(x, y);
}

void AIsometricObject::setCenter(sf::Vector2f center)
{
	this->center = center;
}

void AIsometricObject::setScale(float x, float y)
{
	this->scaleX = x;
	this->scaleY = y;

	if (this->sprite != nullptr)
	{
		this->sprite->setScale(this->scaleX, this->scaleX);
	}
}

sf::Vector2f AIsometricObject::getPosition()
{
	return this->sprite->getWorldPosition();
}

sf::Vector2f AIsometricObject::getScale()
{
	return this->sprite->getScale();
}

sf::FloatRect AIsometricObject::getLocalBounds()
{
	return this->sprite->getLocalBounds();
}
