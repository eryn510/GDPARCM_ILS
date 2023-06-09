#pragma once
#include "AObject.h"

class FPSCounter : public AObject
{
	public:
		FPSCounter();
		~FPSCounter();
		// Inherited via AObject
		virtual void initialize() override;
		virtual void processInput(sf::Event event) override;
		void Update(sf::Time deltaTime) override;
		void Draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates) override;
	
	private:
		sf::Time updateTime;
		sf::Text* statsText;
		int framesPassed = 0;

		int counter;

		float displayDelay = 5.0f;

		void updateFPS(sf::Time elapsedTime);
		
};

