#include "Sim.h"
#include "Globals.h"
#include "Entity.h"
#include "Components.h"
#include "Systems.h"
#include "Events.h"

Sim::Sim() :
	m_window{ sf::VideoMode{Globals::videoWidth, Globals::videoHeight}, "Jam One" }
{
	createSystems();
}

void Sim::execute()
{
	// TEST CODE

	for (int i = 0; i < Globals::tilemapWidth; ++i)
	{
		m_tilemap.push_back(std::vector<int>{});
		for (int j = 0; j < Globals::tilemapHeight; ++j)
		{
			int val = 1;
			if (j == 0 || j == Globals::tilemapHeight - 1 ||
				i == 0 || i == Globals::tilemapWidth - 1) val = 5;
			m_tilemap[i].push_back(val);
		}
	}

	m_blockedTiles.push_back(1);

	SetTilemapEvent ste;
	ste.blockedTiles = &m_blockedTiles;
	ste.tilemap = &m_tilemap;
	broadcastEvent(&ste);

	// END TEST

	sf::Clock clock;
	const float frameTime = 1000.0f / 60.0f;

	while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) m_window.close();
		}

		// Main loop
		if (clock.getElapsedTime().asMilliseconds() >= frameTime)
		{
			// systems

			for (auto &system : m_systems)
			{
				system->execute();
			}

			clock.restart();
		}
	}
}

void Sim::createSystems()
{
	m_systems.push_back(std::make_unique<BehaviorSystem>());
	m_systems.push_back(std::make_unique<RenderSystem>(&m_window));
}