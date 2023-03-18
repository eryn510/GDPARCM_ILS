#pragma once
#include "AObject.h"

class IconObject : public AObject
{
public:
	IconObject(std::string name, int textureIndex);

	// Inherited via AObject
	virtual void initialize() override;
	virtual void processInput(sf::Event event) override;
	virtual void Update(sf::Time deltaTime) override;

public:
	sf::Sprite* getSprite();

private:
	int textureIndex = 0;

};

