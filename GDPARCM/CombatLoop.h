#pragma once
#include "SFML/System.hpp"
#include <vector>
#include "ACharacter.h"
#include "SelectorOption.h"
#include "ProgressBar.h"
#include "UIDisplay.h"
#include "Transition.h"

class CombatLoop
{
public:
	static CombatLoop* getInstance();

	void InitCharacters();

	void processInput(sf::Event event);
	void update(sf::Time deltaTime);

	void goNext();

	void enemyMove();

	std::vector<ACharacter*> characters;
	std::vector<SelectorOption*> options;
	std::vector<UIDisplay*> skillCutIns;

	ACharacter* currentCharacter = nullptr;

	ProgressBar* load = nullptr;

	bool hasLoaded = false;
	bool onSkillCutIn = false;

	//FLAGGER TO IDLE
	bool hasSelected = false;

	float currentFill = 0.0f;

private:
	CombatLoop() {};
	CombatLoop(CombatLoop const&) {};
	CombatLoop& operator=(CombatLoop const&) {};
	static CombatLoop* sharedInstance;

	int currentTurn = 0;
	int optionSelected = 0;

	void turnOffOptions();
	void handleKeyInput(sf::Keyboard::Key key, bool isPressed);

	void playSkillCutIn(float deltaTime);

	float cutInDelta = 0.0f;
	float waitDelta = 0.0f;

	float maxWaitTime = 1.5f;

	bool pressW = false;
	bool pressS = false;
	bool pressEnter = false;

	bool endCutIn = false;

	bool startPlayer = false;

	bool playStandbyAudio = false;

	bool isReleased = true;

	bool transitionCreated = false;

	AObject* optionBoxRef;
	Transition* transitionBox = nullptr;
	UIDisplay* readyDisplay = nullptr;
};

