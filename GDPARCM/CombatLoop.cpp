#include "CombatLoop.h"
#include "Estelle.h"
#include "Joshua.h"
#include "Enemy.h"
#include "ObjectManager.h"
#include <iostream>
#include "MathUtils.h"

#include "AudioManager.h"
#include "TextureManager.h"
#include "UIBox.h"
#include "MainLoop.h"
#include "ObjectPlayer.h"

CombatLoop* CombatLoop::sharedInstance = NULL;

CombatLoop* CombatLoop::getInstance()
{
    if (sharedInstance == NULL) {
        sharedInstance = new CombatLoop();
    }
    return sharedInstance;
}

void CombatLoop::InitCharacters()
{
    Joshua* joshua = new Joshua("Joshua", 1);
    joshua->setScale(2, 2);
    joshua->setPosition(-128, -64);
    joshua->setIdlePos(sf::Vector2f(-128, -64));
    joshua->changeState(IDLE);
    ObjectManager::getInstance()->addObject(joshua);
    characters.push_back(joshua);

    Estelle* estelle = new Estelle("Estelle", 0);
    estelle->setScale(2, 2);
    estelle->setPosition(-32, 32);
    estelle->setIdlePos(sf::Vector2f(-32, 32));
    estelle->changeState(IDLE);
    ObjectManager::getInstance()->addObject(estelle);
    characters.push_back(estelle);

    //MIDDLE
    Enemy* enemy = new Enemy("Enemy", 2);
    enemy->setScale(3, 3);
    enemy->setPosition(128, -240);
    enemy->setIdlePos(sf::Vector2f(128, -240));
    enemy->changeState(IDLE);
    ObjectManager::getInstance()->addObject(enemy);
    characters.push_back(enemy);

    //UPPER
    Enemy* enemy2 = new Enemy("Enemy2", 3);
    enemy2->setScale(3, 3);
    enemy2->setPosition(32, -272);
    enemy2->setIdlePos(sf::Vector2f(32, -272));
    enemy2->changeState(IDLE);
    ObjectManager::getInstance()->addObject(enemy2);
    characters.push_back(enemy2);

    //LOWER
    Enemy* enemy3 = new Enemy("Enemy3", 4);
    enemy3->setScale(3, 3);
    enemy3->setPosition(176, -132);
    enemy3->setIdlePos(sf::Vector2f(176, -132));
    enemy3->changeState(IDLE);
    ObjectManager::getInstance()->addObject(enemy3);
    characters.push_back(enemy3);

    UIBox* optionBox = new UIBox("OptionBox");
    optionBox->setPosition(0, 0);
    ObjectManager::getInstance()->addObject(optionBox);
    this->optionBoxRef = optionBox;

    sf::Vector2u optionTextureSize = optionBox->getSprite()->getTexture()->getSize();

    SelectorOption* selector = new SelectorOption("AttackSelect");
    optionBox->attachChild(selector);
    selector->initialize("Attack", optionTextureSize, sf::Vector2f(0, -100));
    options.push_back(selector);

    SelectorOption* selector2 = new SelectorOption("PassSelect");
    optionBox->attachChild(selector2);
    selector2->initialize("Pass", optionTextureSize);
    options.push_back(selector2);

    SelectorOption* selector3 = new SelectorOption("SpecialSelect");
    optionBox->attachChild(selector3);
    selector3->initialize("Special", optionTextureSize, sf::Vector2f(0, 100));
    options.push_back(selector3);

    load = new ProgressBar("loadBar");
    load->initialize(-(MainLoop::WINDOW_WIDTH / 2), -(MainLoop::WINDOW_HEIGHT / 2), MainLoop::WINDOW_WIDTH, 50, sf::Color::Green, 0);
    load->setFill(0);
    ObjectManager::getInstance()->addObject(load);
}

void CombatLoop::processInput(sf::Event event)
{
        switch (event.type) {
	        case sf::Event::KeyPressed:
	            handleKeyInput(event.key.code, true);
	            break;
	        case sf::Event::KeyReleased:
	            handleKeyInput(event.key.code, false);
                isReleased = true;
                break;
        }
}



void CombatLoop::update(sf::Time deltaTime)
{
    if (!onSkillCutIn)
    {
        for (int i = 0; i < characters.size(); i++)
        {
            if (characters[i]->turnIndex == (currentTurn % characters.size()) && !hasSelected)
            {
                this->optionBoxRef->setEnabled(true);
                characters[i]->changeState(STANDBY);
                this->currentCharacter = characters[i];
                
                if (!playStandbyAudio)
                {
                    if (!this->currentCharacter->standbySFX.empty())
                        this->currentCharacter->standbySFX[MathUtils::randomInt(0, (int)this->currentCharacter->standbySFX.size())]->play();
                    playStandbyAudio = true;
                }
            }
        }

        //HANDLE COMBAT OPTIONS
        if (pressW && isReleased)
        {
            sf::Sound* sound = AudioManager::getInstance()->getAudio("Hover");
            sound->setVolume(100);
            sound->play();
            turnOffOptions();
            if (optionSelected > 0)
                optionSelected--;
            else if (optionSelected <= 0)
                optionSelected = 2;
            std::cout << "W is pressed!" << std::endl;
            isReleased = false;
        }
        else if (pressS && isReleased)
        {
            sf::Sound* sound = AudioManager::getInstance()->getAudio("Hover");
            sound->setVolume(100);
            sound->play();
            turnOffOptions();
            if (optionSelected < options.size() - 1)
                optionSelected++;
            else if (optionSelected >= options.size() - 1)
                optionSelected = 0;
            std::cout << "S is pressed!" << std::endl;
            isReleased = false;
        }

        //SET OPTION BASED FROM KEY INPUT
        options[optionSelected]->isCurrentlySelected = true;

        if (pressEnter && isReleased && !hasSelected)
        {
            hasSelected = true;
            sf::Sound* sound = AudioManager::getInstance()->getAudio("Select");
            sound->setVolume(100);
            sound->play();

            if(!hasLoaded)
            {
                if (optionSelected == 0)
                {
                    this->optionBoxRef->setEnabled(false);
                    this->currentCharacter->changeState(ATTACK);
                    if (!this->currentCharacter->attackSFX.empty())
                        this->currentCharacter->attackSFX[MathUtils::randomInt(0, (int)this->currentCharacter->attackSFX.size())]->play();
                }
                else if (optionSelected == 1)
                {
                    this->optionBoxRef->setEnabled(false);
                    this->currentCharacter->changeState(IDLE);
                    this->currentCharacter->reset();
                    goNext();
                }
            }
            else if (hasLoaded)
            {
                onSkillCutIn = true;
                playStandbyAudio = false;
            }

            isReleased = false;
        }
    }

    else
    {
        this->optionBoxRef->setEnabled(false);
        playSkillCutIn(deltaTime.asSeconds());
    }
    
    
}

void CombatLoop::goNext()
{
    this->hasSelected = false;
    this->optionSelected = 0;
    this->playStandbyAudio = false;
    currentTurn++;
}

void CombatLoop::enemyMove()
{
    this->optionBoxRef->setEnabled(false);
    this->hasSelected = true;
}

void CombatLoop::turnOffOptions()
{
    for (auto opt : options)
        opt->isCurrentlySelected = false;
}

void CombatLoop::handleKeyInput(sf::Keyboard::Key key, bool isPressed)
{
    if (key == sf::Keyboard::W)
        pressW = isPressed;
    else if (key == sf::Keyboard::S)
        pressS = isPressed;
    else if (key == sf::Keyboard::Enter)
        pressEnter = isPressed;
}

void CombatLoop::playSkillCutIn(float deltaTime)
{
    cutInDelta += deltaTime;
    if (cutInDelta <= 0.5f && !endCutIn)
    {
        if (!playStandbyAudio)
        {
            sf::Sound* sound = AudioManager::getInstance()->getAudio("SCraft");
            sound->setVolume(100);
            sound->play();
            playStandbyAudio = true;
        }

        sf::Texture* estelleCutInTex = TextureManager::getInstance()->getFromTextureMap("SkillCutInEstelle", 0);
        sf::Vector2f startPosE = sf::Vector2f(-(float)estelleCutInTex->getSize().x / 2.0f, -(float)estelleCutInTex->getSize().y / 2);
        sf::Vector2f endPosE = sf::Vector2f(0.0f, (float)estelleCutInTex->getSize().y / 2.0f);

        this->skillCutIns[0]->setPosition(MathUtils::lerp(startPosE, endPosE, cutInDelta / 0.5f));

        sf::Texture* joshuaCutInTex = TextureManager::getInstance()->getFromTextureMap("SkillCutInJoshua", 0);
        sf::Vector2f startPosJ = sf::Vector2f((float)joshuaCutInTex->getSize().x / 2.0f, (float)joshuaCutInTex->getSize().y / 2);
        sf::Vector2f endPosJ = sf::Vector2f(0, -((float)joshuaCutInTex->getSize().y / 2));

        this->skillCutIns[1]->setPosition(MathUtils::lerp(startPosJ, endPosJ, cutInDelta / 0.5f));
    }
    else
    {
        endCutIn = true;
        cutInDelta = 0.0f;
        waitDelta += deltaTime;

        if(!transitionCreated)
        {
            Transition* transition = new Transition("FirstTransition", 1.5);
            transition->initialize();
            this->transitionBox = transition;
            ObjectManager::getInstance()->addObject(transition);
            this->transitionBox->setEnabled(true);
            transitionCreated = true;
        }

        if (this->transitionBox != nullptr && this->transitionBox->isFinished)
        {
            if (!startPlayer)
            {
                ObjectPlayer* objectPlayer = new ObjectPlayer("Video Player");
                objectPlayer->initialize();

                ObjectManager::getInstance()->disableAll();

                ObjectManager::getInstance()->addObject(objectPlayer);
                startPlayer = true;
            }
        }
        else
        {
            transitionBox->setEnabled(true);
        }
        
        
    }
}
