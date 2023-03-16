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
#include <iostream>

const sf::Time MainLoop::TIME_PER_FRAME = sf::seconds(1.f / 60.f);

MainLoop::MainLoop() : mWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Application"){
    //mWindow.setFramerateLimit(60);
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

    AudioManager::getInstance()->play("Battle");
    
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

        default: ObjectManager::getInstance()->processInput(event); break;
        case sf::Event::Closed:
            this->mWindow.close();
            break;
        case sf::Event::KeyPressed:
            handlePlayerInput(event.key.code, true);
            break;
        case sf::Event::KeyReleased:
            handlePlayerInput(event.key.code, false);
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
    CombatLoop::getInstance()->update(deltaTime);
    ObjectManager::getInstance()->update(deltaTime);
}

void MainLoop::render() {
    mWindow.clear();
    ObjectManager::getInstance()->draw(&mWindow);
    mWindow.display();
}
