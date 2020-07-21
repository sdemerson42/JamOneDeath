#include "Sim.h"
#include "Globals.h"
#include "Components.h"
#include "Systems.h"
#include "Events.h"
#include "Logger.h"

//TEST
#include "TestLogic.h"
#include "PlayerLogic.h"
#include "GhostLogic.h"
// END TEST

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
	m_entities.push_back(std::make_shared<Entity>());
	Entity& e = *m_entities.back();
	e.setPosition(200.0f, 100.0f);
	auto rc = e.addComponent<RenderComponent>("GFX/Main.png", 0.0f, 0.0f,
		0.0f, 0.0f, 128.0f, 128.0f);
	rc = e.addComponent<RenderComponent>("GFX/Main.png", 0.0f, 0.0f,
		0.0f, 128.0f, 128.0f, 128.0f);
	auto pc = e.addComponent<PhysicsComponent>(true, 10.0f, 100.0f, 108.0f, 28.0f, 1.0f);
	auto ac = e.addComponent<AnimationComponent>();
	ac->addAnimation("main", std::vector<sf::Vector2f>{
		sf::Vector2f{ 0.0f, 0.0f },
			sf::Vector2f{ 128.0f, 0.0f },
			sf::Vector2f{ 0.0f, 0.0f },
			sf::Vector2f{ 256.0f, 0.0f }},
		9);
	ac->addAnimation("idle", std::vector<sf::Vector2f>{
		sf::Vector2f{ 0.0f, 0.0f } },
		1);

	auto bc = e.addComponent<BehaviorComponent>();
	bc->addLogic<PlayerLogic>();
	e.addTag("Natty");
	

	m_entities.push_back(std::make_shared<Entity>());
	Entity& e2 = *m_entities.back();
	e2.setPosition(400.0f, 300.0f);
	auto rc2 = e2.addComponent<RenderComponent>("GFX/Main.png", 0.0f, 0.0f,
		0.0f, 256.0f, 128.0f, 128.0f);
	auto pc2 = e2.addComponent<PhysicsComponent>(true, 10.0f, 100.0f, 108.0f, 28.0f, 1.0f);
	auto bc2 = e2.addComponent<BehaviorComponent>();
	bc2->addLogic<GhostLogic>();
	auto ac2 = e2.addComponent<AnimationComponent>();
	ac2->addAnimation("main", std::vector<sf::Vector2f>{
		sf::Vector2f{ 0.0f, 256.0f },
			sf::Vector2f{ 128.0f, 256.0f },
			sf::Vector2f{ 0.0f, 256.0f },
			sf::Vector2f{ 256.0f, 256.0f }},
		6);
	ac2->playAnimation("main", true);

	// END TEST
}