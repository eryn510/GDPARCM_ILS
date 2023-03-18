#include "ObjectPlayer.h"
#include "TextureManager.h"
#include "AudioManager.h"
#include "FPSCounter.h"
#include "MainLoop.h"
#include "ObjectManager.h"

ObjectPlayer::ObjectPlayer(std::string name) : AObject(name)
{
	this->TextureList = TextureManager::getInstance()->getStreamingTextures();
}

void ObjectPlayer::initialize()
{
	this->sprite = new sf::Sprite();
	this->startText = new sf::Text();

	sf::Font* font = new sf::Font();

	font->loadFromFile("Media/Sansation.ttf");

	this->startText->setFont(*font);
	this->startText->setString("Press START to play!");
	this->startText->setCharacterSize(36);
	this->startText->setFillColor(sf::Color::Black);
	this->startText->setOrigin(this->startText->findCharacterPos(this->startText->getString().getSize() / 2).x,
	this->startText->getCharacterSize() / 2);
	this->startText->setPosition(0, 400);
}
void ObjectPlayer::processInput(sf::Event event)
{
}

void ObjectPlayer::Update(sf::Time deltaTime)
{
	if (currentFrame >= this->TextureList.size())
	{
		if (!playMenuBGM)
		{
			AudioManager::getInstance()->play("MainMenu");
			playMenuBGM = true;
		}

		displayText = true;
		this->sprite->setTexture(*TextureManager::getInstance()->getFromTextureMap("Menu", 0));
		this->startText->setFillColor(sf::Color(0, 0, 0, 255 * sin(this->deltaTime)));
	}

	if (hasNotRun) {
		hasNotRun = false;
		AudioManager::getInstance()->getAudio("Battle")->stop();
		AudioManager::getInstance()->play("Intro");
		this->sprite->setTexture(*this->TextureList[currentFrame]);
		this->sprite->setTextureRect(sf::IntRect(0, 0, this->TextureList[currentFrame]->getSize().x, this->TextureList[currentFrame]->getSize().y));
		this->sprite->setOrigin(this->TextureList[currentFrame]->getSize().x / 2, this->TextureList[currentFrame]->getSize().y / 2);
		this->setScale(1920.0f / (float)this->TextureList[currentFrame]->getSize().x, 1080.0f / (float)this->TextureList[currentFrame]->getSize().y);

		FPSCounter* fpsCounter = new FPSCounter();
		ObjectManager::getInstance()->addObject(fpsCounter);
	}

	this->deltaTime += deltaTime.asSeconds();
	
	if (this->deltaTime > FRAME_RATE * (this->currentFrame + 1)) {
		currentFrame++;
		if (currentFrame < this->TextureList.size())
		{
			this->sprite->setTexture(*this->TextureList[currentFrame]);
			this->setScale(1920.0f / (float)this->TextureList[currentFrame]->getSize().x, 1080.0f / (float)this->TextureList[currentFrame]->getSize().y);
		}
	}
}

void ObjectPlayer::Draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates)
{
	AObject::Draw(targetWindow, renderStates);

	if (displayText)
		targetWindow->draw(*this->startText, renderStates);
}
