#pragma once
#include "AObject.h"

class Transition : public AObject
{
public:
	Transition(std::string name, float maxTransitionTime);

	// Inherited via AObject
	virtual void initialize() override;

	virtual void Update(sf::Time deltaTime) override;
	virtual void processInput(sf::Event event) override;
	virtual void Draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates) override;

	bool isFinished = false;

private:
	float deltaTransition;
	float maxTransitionTime = 0;

	sf::RectangleShape* transitionRect;
};
