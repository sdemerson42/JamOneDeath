#include "InputSystem.h"
#include "SFML/Window.hpp"
#include "Events.h"
#include "PlayerLogic.h"

void InputSystem::execute()
{
	// TEST
	float x = 0.0f;
	float y = 0.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) x = -1.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) x = 1.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) y = -1.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) y = 1.0f;
	
	InputEvent ie;
	ie.moveX = x;
	ie.moveY = y;
	
	PlayerLogic::setInput(ie);

	// END TEST
}