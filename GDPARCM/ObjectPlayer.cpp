#include "ObjectPlayer.h"
#include "TextureManager.h"
#include "AudioManager.h"

ObjectPlayer::ObjectPlayer(std::string name) : AObject(name)
{
	this->TextureList = TextureManager::getInstance()->getStreamingTextures();
}

void ObjectPlayer::initialize()
{
	this->sprite = new sf::Sprite();
}
void ObjectPlayer::processInput(sf::Event event)
{
	
}

void ObjectPlayer::Update(sf::Time deltaTime)
{
	if (currentFrame >= this->TextureList.size())
	{
		this->sprite->setTexture(*TextureManager::getInstance()->getFromTextureMap("Menu", 0));
		return;
	}

	if (hasNotRun) {
		hasNotRun = false;
		AudioManager::getInstance()->getAudio("Battle")->stop();
		AudioManager::getInstance()->play("Intro");
		this->sprite->setTexture(*this->TextureList[currentFrame]);
		this->sprite->setTextureRect(sf::IntRect(0, 0, this->TextureList[currentFrame]->getSize().x, this->TextureList[currentFrame]->getSize().y));
		this->sprite->setOrigin(this->TextureList[currentFrame]->getSize().x / 2, this->TextureList[currentFrame]->getSize().y / 2);
		this->setScale(1920.0f / (float)this->TextureList[currentFrame]->getSize().x, 1080.0f / (float)this->TextureList[currentFrame]->getSize().y);
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