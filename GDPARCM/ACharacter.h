#pragma once
#include "AIsometricObject.h"
#include <vector>

enum STATE
{
	IDLE = 0,
	ATTACK,
	NONE
};

class ACharacter : public AIsometricObject
{
public:
	ACharacter(std::string name);

	// Inherited via AIsometricObject
	virtual void Update(sf::Time deltaTime) override;

	void changeState(STATE state);

protected:
	int health = 100;
	STATE state = IDLE;

	std::vector<sf::Texture*> idleSprites;
	std::vector<sf::Texture*> attackSprites;

};

