#include "CombatLoop.h"
#include "Estelle.h"
#include "Joshua.h"
#include "Enemy.h"
#include "ObjectManager.h"

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
    Joshua* joshua = new Joshua("Joshua", 2);
    joshua->setScale(2, 2);
    joshua->setPosition(-128, -64);
    joshua->setIdlePos(sf::Vector2f(-128, -64));
    joshua->changeState(IDLE);
    ObjectManager::getInstance()->addObject(joshua);
    characters.push_back(joshua);

    Estelle* estelle = new Estelle("Estelle", 1);
    estelle->setScale(2, 2);
    estelle->setPosition(-32, 32);
    estelle->setIdlePos(sf::Vector2f(-32, 32));
    estelle->changeState(IDLE);
    ObjectManager::getInstance()->addObject(estelle);
    characters.push_back(estelle);

    //MIDDLE
    Enemy* enemy = new Enemy("Enemy", 3);
    enemy->setScale(3, 3);
    enemy->setPosition(128, -240);
    enemy->setIdlePos(sf::Vector2f(128, -240));
    enemy->changeState(IDLE);
    ObjectManager::getInstance()->addObject(enemy);
    characters.push_back(enemy);

    //UPPER
    Enemy* enemy2 = new Enemy("Enemy2", 4);
    enemy2->setScale(3, 3);
    enemy2->setPosition(32, -272);
    enemy2->setIdlePos(sf::Vector2f(32, -272));
    enemy2->changeState(IDLE);
    ObjectManager::getInstance()->addObject(enemy2);
    characters.push_back(enemy2);

    //LOWER
    Enemy* enemy3 = new Enemy("Enemy3", 5);
    enemy3->setScale(3, 3);
    enemy3->setPosition(176, -132);
    enemy3->setIdlePos(sf::Vector2f(176, -132));
    enemy3->changeState(IDLE);
    ObjectManager::getInstance()->addObject(enemy3);
    characters.push_back(enemy3);
}

void CombatLoop::update(sf::Time deltaTime)
{
    for (int i = 0; i < characters.size(); i++) 
    {
        if (characters[i]->turnIndex == currentTurn)
            characters[i]->changeState(STANDBY);
    }

}
