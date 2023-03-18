#include "Transition.h"
#include "MainLoop.h"
#include "MathUtils.h"

Transition::Transition(std::string name, float maxTransitionTime) : AObject(name), maxTransitionTime(maxTransitionTime)
{
	this->setEnabled(false);
}

void Transition::initialize()
{
	this->transitionRect = new sf::RectangleShape();
	this->transitionRect->setSize(sf::Vector2f(MainLoop::WINDOW_WIDTH, MainLoop::WINDOW_HEIGHT));
	this->transitionRect->setOrigin(this->transitionRect->getSize().x / 2, this->transitionRect->getSize().y / 2);
	this->transitionRect->setFillColor(sf::Color(255, 255, 255, 0));
	//this->setPosition((float)this->transitionRect->getSize().x / 2.0f, (float)this->transitionRect->getSize().y / 2.0f);
}

void Transition::Update(sf::Time deltaTime)
{
	if (this->isEnabled())
	{
		deltaTransition += deltaTime.asSeconds();

		if (deltaTransition <= maxTransitionTime)
		{
			this->transitionRect->setFillColor(sf::Color(255, 255, 255, (int)std::lerp(0, 255, deltaTransition / maxTransitionTime)));
		}
		else
		{
			this->isFinished = true;
			this->setEnabled(false);
		}
	}
}

void Transition::processInput(sf::Event event)
{
}

void Transition::Draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates)
{
	AObject::Draw(targetWindow, renderStates);

	if (this->isEnabled())
		targetWindow->draw(*this->transitionRect, renderStates);
}
