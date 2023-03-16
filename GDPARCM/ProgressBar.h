#pragma once
#include "AObject.h"

class ProgressBar : public AObject
{
public:
	// Inherited via AObject
	virtual void initialize() override;
	virtual void Update(sf::Time deltaTime) override;

private:
	
};

