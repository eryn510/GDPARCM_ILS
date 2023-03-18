#include "AObject.h"
#include <iostream>

AObject::AObject(std::string name) : name(name)
{

}

AObject::~AObject() 
{
	if (this->sprite != NULL) {
		delete this->sprite;
	}	
}

std::string AObject::getName() 
{
	return name;
}

void AObject::attachChild(AObject* child)
{
	this->childList.push_back(child);
	child->initialize();

	child->parent = this;
}

void AObject::detachChild(AObject* child)
{
	int index = -1;
	for (int i = 0; i < this->childList.size(); i++) {
		if (this->childList[i] == child) {
			index = i;
		}
	}

	if (index != -1) {
		this->childList.erase(this->childList.begin() + index);
	}
}

sf::Sprite* AObject::getSprite()
{
	return this->sprite;
}

void AObject::Draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates) 
{
	if (this->sprite != NULL) {
		this->sprite->setPosition(this->posX, this->posY);
		this->sprite->setScale(this->scaleX, this->scaleY);
		if (enabled) {
			targetWindow->draw(*this->sprite, renderStates);
			renderStates.transform = this->sprite->getTransform() * renderStates.transform;
		}
	}

	for (int i = 0; i < this->childList.size(); i++) {
		AObject* child = this->childList[i];
		if (child->isEnabled()) {
			child->Draw(targetWindow, renderStates);
		}
	}
}

void AObject::Update(sf::Time deltaTime) 
{
	// Add Implementation here
}

void AObject::setPosition(float x, float y)
{
	this->posX = x;
	this->posY = y;

	if (this->sprite != nullptr)
	{
		this->sprite->setPosition(this->posX, this->posY);
	}
}

void AObject::setPosition(sf::Vector2f pos)
{
	this->posX = pos.x;
	this->posY = pos.y;

	if (this->sprite != nullptr)
	{
		this->sprite->setPosition(this->posX, this->posY);
	}
}

void AObject::setScale(float x, float y)
{
	this->scaleX = x;
	this->scaleY = y;

	if (this->sprite != nullptr)
	{
		this->sprite->setScale(this->scaleX, this->scaleY);
	}
}

sf::Vector2f AObject::getPosition()
{
	return this->sprite->getPosition();
}

sf::Vector2f AObject::getScale()
{
	return this->sprite->getScale();
}

std::vector<AObject*> AObject::getChildren()
{
	return this->childList;
}

AObject* AObject::getParent()
{
	return this->parent;
}

void AObject::setEnabled(bool flag)
{
	this->enabled = flag;
}

bool AObject::isEnabled()
{
	return this->enabled;
}

sf::FloatRect AObject::getLocalBounds()
{
	return this->sprite->getLocalBounds();
}

