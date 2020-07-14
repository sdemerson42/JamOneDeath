#pragma once

#include <vector>
#include <memory>
#include "SFML/Graphics.hpp"
#include "ISystem.h"

class Sim
{
public:
	Sim();
	void execute();
private:
	sf::RenderWindow m_window;
	std::vector<std::unique_ptr<ISystem>> m_systems;

	void createSystems();
};
