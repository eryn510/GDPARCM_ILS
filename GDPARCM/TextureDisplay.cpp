#include "TextureDisplay.h"
#include <iostream>
#include "TextureManager.h"
#include "MainLoop.h"
#include "ObjectManager.h"
#include "IconObject.h"
TextureDisplay::TextureDisplay(): AObject("TextureDisplay")
{
	
}


void TextureDisplay::Update(sf::Time deltaTime)
{
	this->ticks += MainLoop::TIME_PER_FRAME.asMilliseconds();
	
	if (this->streamingType == StreamingType::BATCH_LOAD && !this->startedStreaming && this->ticks > this->STREAMING_LOAD_DELAY) 
	{
		this->startedStreaming = true;
		this->ticks = 0.0f;
		TextureManager::getInstance()->loadStreamingAssets();

		/*
		while (this->numDisplayed < 50) 
		{
			this->onFinishedExecution();
			this->numDisplayed++;
		}
		*/
	}
	else if (this->streamingType == StreamingType::SINGLE_STREAM && this->ticks > this->STREAMING_LOAD_DELAY) 
	{
		//if (this->numDisplayed < 100) 
		//{
			this->ticks = 0.0f;
			TextureManager::getInstance()->loadSingleStreamAsset(this->numDisplayed, this);
			this->numDisplayed++;
		//}
		
	}
}

void TextureDisplay::initialize()
{
}

void TextureDisplay::onFinishedExecution()
{
	//spawnObject();
}

void TextureDisplay::spawnObject()
{
	std::string objectName = "Icon_" + std::to_string(this->iconList.size());
	IconObject* iconObj = new IconObject(objectName, this->iconList.size());
	this->iconList.push_back(iconObj);

	sf::Vector2u texSize = iconObj->getSprite()->getTexture()->getSize();

	iconObj->getSprite()->setOrigin(texSize.x / 2, texSize.y / 2);
	iconObj->setPosition(0, 0);

	iconObj->setEnabled(false);

	ObjectManager::getInstance()->addObject(iconObj);
}

