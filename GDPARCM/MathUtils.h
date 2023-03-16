#pragma once
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"

class MathUtils
{
public:

	static sf::Vector2f WorldToScreen(sf::Vector2f v)
	{
		return sf::Vector2f(2.0f * v.x, v.y);
	}

	static sf::Vector2f ScreenToWorld(sf::Vector2f v)
	{
		return sf::Vector2f((v.x + 2.0f * v.y) / 4.0f, (2.0f * v.y - v.x) / 4.0f);
	}

	static sf::Vector2f lerp(sf::Vector2f a, sf::Vector2f b, float t) {
		return a * (1 - t) + b * t;
	}

	static const float percentToPixelX(const float percent, sf::VideoMode& vm) 
	{
		return std::floor(static_cast<float>(vm.width) * (percent / 100.f));
	}

	static const float percentToPixelY(const float percent, sf::VideoMode& vm)
	{
		return std::floor(static_cast<float>(vm.height) * (percent / 100.f));
	}
};

