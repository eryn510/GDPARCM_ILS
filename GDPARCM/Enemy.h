#pragma once
#include "ACharacter.h"

class Enemy : public ACharacter
{
public:
	Enemy(std::string name, int turnIndex);

	// Inherited via ACharacter
	virtual void initialize() override;
	virtual void processInput(sf::Event event) override;
	virtual void Update(sf::Time deltaTime) override;

	void setIdlePos(sf::Vector2f pos);
	virtual void reset() override;

private:

	float maxAnimupdate = 0.1f;
	float maxMoveTime = 1.0f;
	float waitTime = 0.0f;
	float animDelta = 0.0f;
	float totalDeltaTime = 0;

	float attackTimer = 0.0f;
	float attackDelay = 2.0f;


	sf::Vector2f idlePos;
	bool endAttack = false;
	bool animEnd = false;

};

