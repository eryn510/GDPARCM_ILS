#pragma once
#include "AObject.h"

class ProgressBar : public AObject
{
public:
	ProgressBar(std::string name);

	// Inherited via AObject
	virtual void initialize() override;
	virtual void initialize(float x, float y, float width, float height,
		sf::Color inner_color, unsigned character_size, sf::Font* font = NULL);

	virtual void Update(sf::Time deltaTime) override;
	virtual void processInput(sf::Event event) override;
	virtual void Draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates) override;

	virtual void setPosition(float x, float y) override;
	virtual void setScale(float x, float y) override;

	virtual sf::Vector2f getPosition() override;
	virtual sf::Vector2f getScale() override;

	void setFill(float percentage);

	float currentFill = 0.0f;

private:
	std::string barString;
	sf::Text text;
	float maxWidth;
	sf::RectangleShape* back;
	sf::RectangleShape* inner;
};

