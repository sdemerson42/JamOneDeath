#include "Sim.h"
#include "Globals.h"
#include "Components.h"
#include "Systems.h"
#include "Events.h"
#include "Logger.h"

Sim::Sim() :
	m_window{ sf::VideoMode{Globals::videoWidth, Globals::videoHeight}, "Jam One" }
{
	createSystems();
	setupScene();
	buildEntities();
}

void Sim::execute()
{
	Logger::log("Begin Sim execution.");

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
	Logger::log("Exiting Sim main loop.");
}

void Sim::createSystems()
{
	m_systems.push_back(std::make_unique<SpawnSystem>(&m_entities));
	m_systems.push_back(std::make_unique<InputSystem>());
	m_systems.push_back(std::make_unique<BehaviorSystem>());
	m_systems.push_back(std::make_unique<AnimationSystem>());
	m_systems.push_back(std::make_unique<PhysicsSystem>());
	m_systems.push_back(std::make_unique<RenderSystem>(&m_window));
}

void Sim::setupScene()
{
	// TEST CODE

	for (int i = 0; i < Globals::tilemapWidth; ++i)
	{
		m_tilemap.push_back(std::vector<int>{});
		for (int j = 0; j < Globals::tilemapHeight; ++j)
		{
			int val = 0;
			if (j == 0 || j == Globals::tilemapHeight - 1 ||
				i == 0 || i == Globals::tilemapWidth - 1) val = 1;
			if (j == Globals::tilemapHeight / 2) val = 1;
			m_tilemap[i].push_back(val);
		}
	}

	m_blockedTiles.push_back(1);

	SetTilemapEvent ste;
	ste.blockedTiles = &m_blockedTiles;
	ste.tilemap = &m_tilemap;
	broadcastEvent(&ste);

	// END TEST
}

void Sim::buildEntities()
{
	// TEST

	SpawnSystem::buildEntity("Natty", 100.0f, 200.0f);
	SpawnSystem::buildEntity("Ghost", 400.0f, 300.0f);
	
	// END TEST
}