#pragma once
#include "AObject.h"
#include "UIDisplay.h"

enum Character {
	ESTELLE,
	JOSHUA
};

class StatusBar : public AObject
{
public:
	StatusBar(std::string name, Character character);

	// Inherited via AObject
	virtual void initialize() override;
	virtual void Update(sf::Time deltaTime) override;

	Character character;
};

