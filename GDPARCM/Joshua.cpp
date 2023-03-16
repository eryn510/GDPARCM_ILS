#include "Joshua.h"
#include <iostream>
#include "TextureManager.h"
#include "MathUtils.h"

Joshua::Joshua(std::string name, int turnIndex) : ACharacter(name)
{
	std::cout << "Declared as " << name << "\n";

	this->turnIndex = turnIndex;

	//assign texture
	this->sprite = new IsometricMapSprite();
	for (int i = 1; i <= 8; i++)
		this->idleSprites.push_back(TextureManager::getInstance()->getFromTextureMap("JoshuaIdle" + std::to_string(i), 0));

	for (int i = 1; i <= 14; i++)
		this->attackSprites.push_back(TextureManager::getInstance()->getFromTextureMap("JoshuaA" + std::to_string(i), 0));

	for (int i = 1; i <= 4; i++)
		this->standbySprites.push_back(TextureManager::getInstance()->getFromTextureMap("JoshuaS" + std::to_string(i), 0));

	sf::Texture* texture = this->idleSprites[idleCounter];
	this->sprite->setTexture(*texture);
	this->sprite->setTextureRect(sf::IntRect(0, 0, texture->getSize().x, texture->getSize().y));
	idleCounter++;

}

void Joshua::initialize()
{
}

void Joshua::Update(sf::Time deltaTime)
{
	totalDeltaTime += deltaTime.asSeconds();
	animDelta += deltaTime.asSeconds();
	if (state == IDLE)
	{
		attackCounter = 0;

		if (idleCounter == this->idleSprites.size())
			idleCounter = 0;

		if (totalDeltaTime >= maxAnimupdate)
		{
			this->sprite->setTexture(*this->idleSprites[idleCounter]);
			this->sprite->setTextureRect(sf::IntRect(0, 0, this->idleSprites[idleCounter]->getSize().x, this->idleSprites[idleCounter]->getSize().y));
			idleCounter++;
			totalDeltaTime = 0;
		}

	}

	else if (state == STANDBY) 
	{
		//WAIT FOR COMMAND

		//ANIMATION
		attackCounter = 0;
		idleCounter = 0;

		if (standbyCounter == this->standbySprites.size())
			standbyCounter = 0;

		if (totalDeltaTime >= maxAnimupdate)
		{
			this->sprite->setTexture(*this->standbySprites[standbyCounter]);
			this->sprite->setTextureRect(sf::IntRect(0, 0, this->standbySprites[standbyCounter]->getSize().x, this->standbySprites[standbyCounter]->getSize().y));
			standbyCounter++;
			totalDeltaTime = 0;
		}
	}

	else if (state = ATTACK)
	{
		if (attackCounter >= this->attackSprites.size()) {
			animEnd = true;
			waitTime += deltaTime.asSeconds();
		}

		if (animDelta >= (maxMoveTime) / (float)this->attackSprites.size() && attackCounter < this->attackSprites.size() && endAttack)
		{
			this->sprite->setTexture(*this->attackSprites[attackCounter]);
			this->sprite->setTextureRect(sf::IntRect(0, 0, this->attackSprites[attackCounter]->getSize().x, this->attackSprites[attackCounter]->getSize().y));
			animDelta = 0;
			totalDeltaTime = 0;
			std::cout << attackCounter << std::endl;
			attackCounter++;
		}

		if (totalDeltaTime <= maxMoveTime && !endAttack)
		{
			if (animDelta >= (maxMoveTime) / (float)this->attackSprites.size())
			{
				this->sprite->setTexture(*this->attackSprites[attackCounter]);
				this->sprite->setTextureRect(sf::IntRect(0, 0, this->attackSprites[attackCounter]->getSize().x, this->attackSprites[attackCounter]->getSize().y));
				attackCounter++;
				animDelta = 0;
				std::cout << attackCounter << std::endl;
			}
			this->setPosition(MathUtils::lerp(this->idlePos, sf::Vector2f(128, -128), totalDeltaTime / maxMoveTime));
		}

		else
			endAttack = true;

		if (animEnd && waitTime >= 2.0f)
		{
			if (totalDeltaTime <= maxMoveTime - 0.5f)
			{
				this->setPosition(MathUtils::lerp(sf::Vector2f(128, -128), this->idlePos, totalDeltaTime / (maxMoveTime - 0.5f)));
			}
			else if (totalDeltaTime > maxMoveTime - 0.5f)
			{
				reset();
				this->changeState(IDLE);
			}
		}
		else if (animEnd && waitTime < 3.0f)
		{
			totalDeltaTime = 0;
		}
	}
}

void Joshua::setIdlePos(sf::Vector2f pos)
{
	this->idlePos = pos;
}

void Joshua::reset()
{
	idleCounter = 0;
	attackCounter = 0;
	waitTime = 0.0f;
	animDelta = 0.0f;
	totalDeltaTime = 0;
	endAttack = false;
	animEnd = false;
}
