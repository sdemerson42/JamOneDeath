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
	
	m_input.moveX = x;
	m_input.moveY = y;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		if (m_input.e == 0) m_input.e = 1;
		else m_input.e = 2;
	}
	else m_input.e = 0;
	
	PlayerLogic::setInput(m_input);

	// END TEST
}