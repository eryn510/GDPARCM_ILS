#pragma once
#include "AObject.h"

class UIBox : public AObject
{

public:
	UIBox(std::string name);

	// Inherited via AObject
	virtual void initialize() override;
	virtual void processInput(sf::Event event) override;
	virtual void Update(sf::Time deltaTime) override;
};

