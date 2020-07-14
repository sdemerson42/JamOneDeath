#include "Sim.h"
#include "Globals.h"
#include "Entity.h"
#include "Components.h"
#include "Systems.h"

Sim::Sim() :
	m_window{ sf::VideoMode{Globals::videoWidth, Globals::videoHeight}, "Jam One" }
{
	createSystems();
}

void Sim::execute()
{
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