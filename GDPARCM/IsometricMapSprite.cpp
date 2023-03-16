#include "IsometricMapSprite.h"
#include "MathUtils.h"

IsometricMapSprite::IsometricMapSprite()
{
}

IsometricMapSprite::IsometricMapSprite(const sf::Image& image, const sf::Vector2f& position, const sf::Vector2f& scale, float rotation, const sf::Color& color)
{
}

IsometricMapSprite::~IsometricMapSprite()
{
}

void IsometricMapSprite::setWorldPosition(float x, float y)
{
	m_worldpos = sf::Vector2f(x,y);
	sf::Vector2f screenPos = MathUtils::WorldToScreen(sf::Vector2f(x, y));
	screenPos.y -= m_z;
	setPosition(screenPos);
}

void IsometricMapSprite::setWorldPosition(const sf::Vector2f& position)
{
	m_worldpos = position;
	sf::Vector2f screenPos = MathUtils::WorldToScreen(position);
	screenPos.y -= m_z;
	setPosition(screenPos);
}

sf::Vector2f IsometricMapSprite::getWorldPosition() const
{
	return this->m_worldpos;
}

void IsometricMapSprite::setWorldZ(float z)
{
	m_z = z;
	sf::Vector2f screenPos = MathUtils::WorldToScreen(m_worldpos);
	screenPos.y -= m_z;
	setPosition(screenPos);
}
