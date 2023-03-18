#pragma once
#include "AObject.h"
class UIDisplay : public AObject
{
public:
	UIDisplay(std::string name, sf::Texture* tex, float width = 0, float height = 0);

	// Inherited via AObject
	virtual void initialize() override;
	virtual void processInput(sf::Event event) override;
	virtual void Update(sf::Time deltaTime) override;
};

