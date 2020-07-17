#pragma once

#include <vector>
#include <memory>
#include "SFML/Graphics.hpp"
#include "ISystem.h"
#include "EventHandler.h"
#include "Entity.h"

class Sim : public EventHandler
{
public:
	Sim();
	void execute();
private:
	sf::RenderWindow m_window;
	std::vector<std::unique_ptr<ISystem>> m_systems;
	std::vector<std::vector<int>> m_tilemap;
	std::vector<int> m_blockedTiles;
	std::vector<std::unique_ptr<Entity>> m_entities;

	void createSystems();
	void setupScene();
	void buildEntities();
};
