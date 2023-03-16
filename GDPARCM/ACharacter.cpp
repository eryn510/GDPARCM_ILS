#include "ACharacter.h"

ACharacter::ACharacter(std::string name) : AIsometricObject(name)
{
}

void ACharacter::Update(sf::Time deltaTime)
{
}

void ACharacter::changeState(STATE state)
{
	this->state = state;
}
