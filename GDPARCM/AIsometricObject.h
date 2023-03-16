#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "IsometricMapSprite.h"
#include "AObject.h"

class AIsometricObject : public AObject
{
public:
	AIsometricObject(std::string name);
	virtual ~AIsometricObject();

	virtual void Update(sf::Time deltaTime) = 0;
	virtual void Draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates);

	std::string getName();

	virtual void setPosition(float x, float y);
	virtual void setPosition(sf::Vector2f pos);
	virtual void setCenter(float x, float y);
	virtual void setCenter(sf::Vector2f center);
	virtual void setScale(float x, float y);
	virtual sf::FloatRect getLocalBounds();
	virtual sf::Vector2f getPosition();
	virtual sf::Vector2f getScale();

protected:
	std::string name;
	IsometricMapSprite* sprite;
	sf::Texture* texture;

	float posX = 0.0f; float posY = 0.0f;
	float scaleX = 1.0f; float scaleY = 1.0f;
	sf::Vector2f center = sf::Vector2f(0,0);

};

