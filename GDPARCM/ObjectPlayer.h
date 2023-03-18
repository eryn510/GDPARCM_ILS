#pragma once
#include "AObject.h"
#include <vector>

class ObjectPlayer : public AObject
{
public:
	ObjectPlayer(std::string name);

	// Inherited via AObject
	virtual void initialize() override;
	virtual void processInput(sf::Event event) override;
	virtual void Update(sf::Time deltaTime) override;

private:
	std::vector<sf::Texture*> TextureList;

	int currentFrame = 0;
	bool hasNotRun = true;

	const float FRAME_RATE = 1.0f / 10.0;

	float deltaTime = 0;
};
