#pragma once
#include "AObject.h"

class Box : public AObject
{
public:
	Box(std::string name, sf::Color color);

	// Inherited via AObject
	virtual void initialize() override;

	virtual void Update(sf::Time deltaTime) override;
	virtual void processInput(sf::Event event) override;
	virtual void Draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates) override;

private:
	sf::Color color;
	sf::RectangleShape* transitionRect;
};