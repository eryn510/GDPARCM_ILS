#pragma once
#include "AObject.h"
class SelectorOption : public AObject
{
public:
	SelectorOption(std::string name);

	// Inherited via AObject
	virtual void initialize() override;
	virtual void initialize(std::string OptionText, sf::Vector2u textureSize = sf::Vector2u(0,0), 
		sf::Vector2f posMove = sf::Vector2f(0,0));
	virtual void processInput(sf::Event event) override;
	virtual void Update(sf::Time deltaTime) override;

	virtual void Draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates) override;

	bool isCurrentlySelected = false;

private:
	sf::Text* text;
};

