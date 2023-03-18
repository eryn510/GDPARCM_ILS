#pragma once
#include "AObject.h"
class BGObject : public AObject
{
public:
	BGObject(std::string name);

	// Inherited via AObject
	virtual void initialize() override;
	virtual void processInput(sf::Event event) override;
	virtual void Update(sf::Time deltaTime) override;

private:
	const float SPEED_MULTIPLIER = 100.0f;
};

