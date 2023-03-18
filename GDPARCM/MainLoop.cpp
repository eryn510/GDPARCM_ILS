#include "MainLoop.h"
#include "TextureManager.h"
#include "BGObject.h"
#include "IconObject.h"
#include "ObjectManager.h"
#include "TextureDisplay.h"
#include "FPSCounter.h"
#include "IsometricMap.h"
#include "Estelle.h"
#include "Joshua.h"
#include "Enemy.h"
#include "StatusBar.h"
#include "AudioManager.h"
#include "CombatLoop.h"
#include "Transition.h"
#include <iostream>

const sf::Time MainLoop::TIME_PER_FRAME = sf::seconds(1.f / 60.f);

MainLoop::MainLoop() : mWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Application", sf::Style::Fullscreen){
    //mWindow.setFramerateLimit(60);
    //mWindow.setKeyRepeatEnabled(false);
    //mWindow.setVerticalSyncEnabled(false);

    TextureManager::getInstance()->loadFromAssetList();
    AudioManager::getInstance()->loadAllAudio();

    //load objects
    //BGObject* bgObject = new BGObject("BGObject");
    //ObjectManager::getInstance()->addObject(bgObject);


    IsometricMap* isoMap = new IsometricMap(32,32);
    isoMap->initializeMap();
    
    CombatLoop::getInstance()->InitCharacters();

    //charRef = enemy;


    TextureDisplay* display = new TextureDisplay();
    ObjectManager::getInstance()->addObject(display);

    FPSCounter* fpsCounter = new FPSCounter();
    ObjectManager::getInstance()->addObject(fpsCounter);

    float UISpacing = 50.0f;
    sf::Vector2f StatusBarDim = sf::Vector2f(400.0f, 200.0f);

    StatusBar* EstelleDisplay = new StatusBar("EstelleDisplay", ESTELLE);
    EstelleDisplay->setPosition(-(WINDOW_WIDTH / 2) + UISpacing + (StatusBarDim.x * 0.5), (WINDOW_HEIGHT / 2) - (StatusBarDim.y / 2));
    ObjectManager::getInstance()->addObject(EstelleDisplay);
    EstelleDisplay->initialize();
    
    StatusBar* JoshuaDisplay = new StatusBar("JoshuaDisplay", JOSHUA);
    JoshuaDisplay->setPosition(-(WINDOW_WIDTH / 2)  + UISpacing * 2 + (StatusBarDim.x * 1.5), (WINDOW_HEIGHT / 2) - (StatusBarDim.y / 2));
    ObjectManager::getInstance()->addObject(JoshuaDisplay);
    JoshuaDisplay->initialize();

    sf::Texture* estelleCutInTex = TextureManager::getInstance()->getFromTextureMap("SkillCutInEstelle", 0);
    UIDisplay* estelleCutIn = new UIDisplay("estelleCutIn", estelleCutInTex, 0);
    estelleCutIn->getSprite()->setOrigin((float)estelleCutInTex->getSize().x / 2.0f, (float)estelleCutInTex->getSize().y);
    //STARTPOS
    estelleCutIn->setPosition(-(float)estelleCutInTex->getSize().x / 2.0f, -(float)estelleCutInTex->getSize().y / 2);
    //ENDPOS
    //estelleCutIn->setPosition(0, estelleCutInTex->getSize().y / 2);
    ObjectManager::getInstance()->addObject(estelleCutIn);
    CombatLoop::getInstance()->skillCutIns.push_back(estelleCutIn);

    sf::Texture* joshuaCutInTex = TextureManager::getInstance()->getFromTextureMap("SkillCutInJoshua", 0);
    UIDisplay* joshuaCutIn = new UIDisplay("joshuaCutIn", joshuaCutInTex, 0);
    joshuaCutIn->getSprite()->setOrigin((float)joshuaCutInTex->getSize().x / 2.0f, 0);
    //STARTPOS
    joshuaCutIn->setPosition((float)joshuaCutInTex->getSize().x / 2.0f, (float)joshuaCutInTex->getSize().y / 2);
    //ENDPOS
    //joshuaCutIn->setPosition(0, -((float)joshuaCutInTex->getSize().y / 2));
    ObjectManager::getInstance()->addObject(joshuaCutIn);
    CombatLoop::getInstance()->skillCutIns.push_back(joshuaCutIn);

    AudioManager::getInstance()->play("Battle");

    Box* backBox = new Box("BackBox", sf::Color::Black);
    backBox->initialize();
    this->backBox = backBox;
    ObjectManager::getInstance()->addObject(backBox);

    Transition* transition = new Transition("FirstTransition", 3.0);
    transition->initialize();
    this->transitionBox = transition;
    ObjectManager::getInstance()->addObject(transition);

}

void MainLoop::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen()) {

        sf::Time deltaTime = clock.restart();
        timeSinceLastUpdate += deltaTime;
        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }

        render();
    }
}


void MainLoop::processEvents() {

    sf::Event event;
    if (this->mWindow.pollEvent(event)) {
        switch (event.type) {

        default: ObjectManager::getInstance()->processInput(event); CombatLoop::getInstance()->processInput(event); break;
        case sf::Event::Closed:
            this->mWindow.close();
            break;
        }
    }
}
void MainLoop::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::W)
        mIsMovingUp = isPressed;
    else if (key == sf::Keyboard::S)
        mIsMovingDown = isPressed;
    else if (key == sf::Keyboard::A)
        mIsMovingLeft = isPressed;
    else if (key == sf::Keyboard::D)
        mIsMovingRight = isPressed;
}

void MainLoop::update(sf::Time deltaTime)
{
    if (transitionBox->isFinished)
    {
        backBox->setEnabled(false);
        CombatLoop::getInstance()->update(deltaTime);
    }
    else
    {
        transitionBox->setEnabled(true);
        backBox->setEnabled(true);
    }

    ObjectManager::getInstance()->update(deltaTime);
}

void MainLoop::render() {
    mWindow.clear();
    ObjectManager::getInstance()->draw(&mWindow);
    mWindow.display();
}
