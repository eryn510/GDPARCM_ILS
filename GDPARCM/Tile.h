#pragma once
#include "AIsometricObject.h"
class Tile : public AIsometricObject
{
public:
	Tile(std::string name);

	// Inherited via AIsometricObject
	virtual void initialize() override;
	virtual void Update(sf::Time deltaTime) override;
};

