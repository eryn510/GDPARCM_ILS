#pragma once
#include "SFML/Graphics.hpp"

class IsometricMapSprite : public sf::Sprite
{
public:
	IsometricMapSprite();
	IsometricMapSprite(const sf::Image& image, const sf::Vector2f &position=sf::Vector2f(0, 0),
		const sf::Vector2f& scale = sf::Vector2f(1, 1), float rotation = 0.f, const sf::Color &color=sf::Color(255, 255, 255, 255));
	~IsometricMapSprite();

	void setWorldPosition(float x, float y);
	void setWorldPosition(const sf::Vector2f& position);
	sf::Vector2f getWorldPosition() const;

	void setWorldZ(float z);
	float getWorldZ() { return m_z; }

protected:
	sf::Vector2f m_worldpos;
	float m_z;
};

