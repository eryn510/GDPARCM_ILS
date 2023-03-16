#pragma once
#include "AIsometricObject.h"
#include <vector>

enum STATE
{
	IDLE = 0,
	STANDBY,
	ATTACK,
	NONE
};

class CombatLoop;

class ACharacter : public AIsometricObject
{
public:
	ACharacter(std::string name);

	// Inherited via AIsometricObject
	virtual void Update(sf::Time deltaTime) override;

	void changeState(STATE state);

protected:
	int health = 100;
	int attack = 10;
	int turnIndex;
	STATE state = IDLE;

	int idleCounter = 0;
	int attackCounter = 0;
	int standbyCounter = 0;

	std::vector<sf::Texture*> idleSprites;
	std::vector<sf::Texture*> attackSprites;
	std::vector<sf::Texture*> standbySprites;

private:

	friend class CombatLoop;

};

