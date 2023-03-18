#include "TextureDisplay.h"
#include <iostream>

#include "AudioManager.h"
#include "TextureManager.h"
#include "MainLoop.h"
#include "ObjectManager.h"
#include "IconObject.h"
#include "ObjectPlayer.h"
#include "CombatLoop.h"

TextureDisplay::TextureDisplay(): AObject("TextureDisplay")
{
	
}


void TextureDisplay::Update(sf::Time deltaTime)
{
	this->ticks += deltaTime.asMilliseconds();
	
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
			TextureManager::getInstance()->loadSingleStreamAsset(this->texIndex, this);
			this->texIndex++;
		//}
		
	}
}

void TextureDisplay::initialize()
{
}

void TextureDisplay::processInput(sf::Event event)
{
}

void TextureDisplay::onFinishedExecution()
{
	checkProgress();
}

void TextureDisplay::checkProgress()
{
	loadedTex++;

	CombatLoop::getInstance()->load->setFill((float)this->loadedTex / (float)TextureManager::getInstance()->getStreamingCount());

	if (this->loadedTex >= TextureManager::getInstance()->getStreamingCount())
	{
		CombatLoop::getInstance()->hasLoaded = true;
		AudioManager::getInstance()->getAudio("SCraftReady")->play();
		this->setEnabled(false);
	}
}

