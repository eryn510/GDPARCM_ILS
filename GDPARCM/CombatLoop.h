#pragma once
#include "SFML/System.hpp"
#include <vector>
#include "ACharacter.h"

class CombatLoop
{
public:
	static CombatLoop* getInstance();

	void InitCharacters();

	void update(sf::Time deltaTime);

	std::vector<ACharacter*> characters;

private:
	CombatLoop() {};
	CombatLoop(CombatLoop const&) {};
	CombatLoop& operator=(CombatLoop const&) {};
	static CombatLoop* sharedInstance;

	int currentTurn = 1;

};

