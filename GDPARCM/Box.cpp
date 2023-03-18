#include "Box.h"
#include "MainLoop.h"
#include "MathUtils.h"

Box::Box(std::string name, sf::Color color) : AObject(name), color(color)
{
	this->setEnabled(false);
}

void Box::initialize()
{
	this->transitionRect = new sf::RectangleShape();
	this->transitionRect->setSize(sf::Vector2f(MainLoop::WINDOW_WIDTH, MainLoop::WINDOW_HEIGHT));
	this->transitionRect->setOrigin(this->transitionRect->getSize().x / 2, this->transitionRect->getSize().y / 2);
	this->transitionRect->setFillColor(color);
	//this->setPosition((float)this->transitionRect->getSize().x / 2.0f, (float)this->transitionRect->getSize().y / 2.0f);
}

void Box::Update(sf::Time deltaTime)
{

}

void Box::processInput(sf::Event event)
{
}

void Box::Draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates)
{
	AObject::Draw(targetWindow, renderStates);

	if (this->isEnabled())
		targetWindow->draw(*this->transitionRect, renderStates);
}