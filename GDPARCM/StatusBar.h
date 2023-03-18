#pragma once
#include "AObject.h"
#include "UIDisplay.h"
#include "ProgressBar.h"

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
	virtual void processInput(sf::Event event) override;
	virtual void Update(sf::Time deltaTime) override;

	Character character;

private:
	ProgressBar* spBar = nullptr;
};

