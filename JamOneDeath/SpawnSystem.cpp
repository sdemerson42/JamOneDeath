#include "SpawnSystem.h"
#include "Components.h"
#include "PlayerLogic.h"
#include "GhostLogic.h"
#include <algorithm>


std::vector<std::shared_ptr<Entity>> SpawnSystem::s_entities;
std::vector<unsigned int> SpawnSystem::s_guids;
std::vector<std::shared_ptr<Entity>>* SpawnSystem::s_simEntities;

void SpawnSystem::execute()
{
	for (unsigned int guid : s_guids)
	{
		auto iter = std::find_if(std::begin(*s_simEntities),
			std::end(*s_simEntities), [=](const std::shared_ptr<Entity>& sp)
			{
				return sp->guid() == guid;
			});

		if (iter != std::end(*s_simEntities))
		{
			s_simEntities->erase(iter);
		}
	}
	s_guids.clear();

	for (auto& sp : s_entities)
	{
		s_simEntities->push_back(std::shared_ptr<Entity>(sp));
		s_simEntities->back()->activateComponents();
	}
	s_entities.clear();
}

void SpawnSystem::buildNatty(float xPos, float yPos)
{
	s_entities.push_back(std::make_shared<Entity>());
	Entity& e = *s_entities.back();
	e.setPosition(xPos, yPos);
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
}

void SpawnSystem::buildGhost(float posX, float posY)
{
	s_entities.push_back(std::make_shared<Entity>());
	Entity& e2 = *s_entities.back();
	e2.setPosition(posX, posX);
	auto rc2 = e2.addComponent<RenderComponent>("GFX/Main.png", 0.0f, 0.0f,
		0.0f, 256.0f, 128.0f, 128.0f);
	auto pc2 = e2.addComponent<PhysicsComponent>(false, 10.0f, 100.0f, 108.0f, 28.0f, 1.0f);
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
}