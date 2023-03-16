#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class AObject
{
public:
	AObject(std::string name);
	virtual ~AObject();
	virtual void initialize() = 0;

	virtual void Update(sf::Time deltaTime) = 0;
	virtual void Draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates);

	std::string getName();

	void attachChild(AObject* child);
	void detachChild(AObject* child);

	virtual void setPosition(float x, float y);
	virtual void setScale(float x, float y);
	virtual sf::FloatRect getLocalBounds();
	virtual sf::Vector2f getPosition();
	virtual sf::Vector2f getScale();

	std::vector<AObject*> getChildren();
	AObject* getParent();

	void setEnabled(bool flag);
	bool isEnabled();

protected:
	std::string name;
	sf::Sprite* sprite;
	sf::Texture* texture;

	std::vector<AObject*> childList;
	AObject* parent = NULL;

	float posX = 0.0f; float posY = 0.0f;
	float scaleX = 1.0f; float scaleY = 1.0f;

private:
	bool enabled = true;

};

