#include "SpawnSystem.h"
#include "Components.h"
#include "PlayerLogic.h"
#include "GhostLogic.h"
#include "DuckLogic.h"
#include "FireballLogic.h"
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

Entity* SpawnSystem::buildNatty()
{
	s_entities.push_back(std::make_shared<Entity>());
	Entity& e = *s_entities.back();
	auto rc = e.addComponent<RenderComponent>("GFX/Main.png", 0.0f, 0.0f,
		0.0f, 0.0f, 128.0f, 128.0f);
	rc = e.addComponent<RenderComponent>("GFX/Main.png", 0.0f, 0.0f,
		0.0f, 128.0f, 128.0f, 128.0f);
	auto pc = e.addComponent<PhysicsComponent>(true, 32.0f, 32.0f, 64.0f, 96.0f, 1.0f);
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
	ac->addAnimation("poof", std::vector<sf::Vector2f>{
		sf::Vector2f{ 0.0f, 512.0f },
			sf::Vector2f{ 128.0f, 512.0f },
			sf::Vector2f{ 256.0f, 512.0f },
			sf::Vector2f{ 384.0f, 512.0f }},
		6);
	ac->addAnimation("rpoof", std::vector<sf::Vector2f>{
		sf::Vector2f{ 384.0f, 512.0f },
			sf::Vector2f{ 256.0f, 512.0f },
			sf::Vector2f{ 128.0f, 512.0f },
			sf::Vector2f{ 0.0f, 512.0f }},
		6);

	auto bc = e.addComponent<BehaviorComponent>();
	bc->addLogic<PlayerLogic>();
	e.addTag("player");
	return &e;
}

Entity* SpawnSystem::buildGhost()
{
	s_entities.push_back(std::make_shared<Entity>());
	Entity& e2 = *s_entities.back();
	auto rc2 = e2.addComponent<RenderComponent>("GFX/Main.png", 0.0f, 0.0f,
		0.0f, 256.0f, 128.0f, 128.0f);
	auto pc2 = e2.addComponent<PhysicsComponent>(false, 32.0f, 32.0f, 64.0f, 96.0f, 1.0f);
	auto bc2 = e2.addComponent<BehaviorComponent>();
	auto logic = bc2->addLogic<GhostLogic>();
	logic->setTarget(s_entities[0].get());	// Terrible hack, but jam time is running out
	auto ac2 = e2.addComponent<AnimationComponent>();
	ac2->addAnimation("main", std::vector<sf::Vector2f>{
		sf::Vector2f{ 0.0f, 256.0f },
			sf::Vector2f{ 128.0f, 256.0f },
			sf::Vector2f{ 0.0f, 256.0f },
			sf::Vector2f{ 256.0f, 256.0f }},
		6);
	ac2->playAnimation("main", true);

	e2.addTag("mob");
	e2.addTag("ghost");
	return &e2;
}

Entity* SpawnSystem::buildDuck()
{
	s_entities.push_back(std::make_shared<Entity>());
	Entity& e2 = *s_entities.back();
	auto rc2 = e2.addComponent<RenderComponent>("GFX/Main.png", 0.0f, 0.0f,
		0.0f, 256.0f, 128.0f, 128.0f);
	auto pc2 = e2.addComponent<PhysicsComponent>(true, 32.0f, 32.0f, 64.0f, 96.0f, 1.0f);
	auto bc2 = e2.addComponent<BehaviorComponent>();
	bc2->addLogic<DuckLogic>();
	auto ac2 = e2.addComponent<AnimationComponent>();
	ac2->addAnimation("main", std::vector<sf::Vector2f>{
		sf::Vector2f{ 0.0f, 384.0f },
			sf::Vector2f{ 128.0f, 384.0f },
			sf::Vector2f{ 0.0f, 384.0f },
			sf::Vector2f{ 256.0f, 384.0f }},
		10);
	ac2->playAnimation("main", true);

	e2.addTag("mob");
	e2.addTag("ghost");
	return &e2;
}

Entity* SpawnSystem::buildFireball()
{
	s_entities.push_back(std::make_shared<Entity>());
	Entity& e2 = *s_entities.back();
	auto rc2 = e2.addComponent<RenderComponent>("GFX/Main.png", 0.0f, 0.0f,
		0.0f, 256.0f, 64.0f, 64.0f);
	auto pc2 = e2.addComponent<PhysicsComponent>(true, 10.0f, 10.0f, 44.0f, 44.0f, 1.0f);
	auto bc2 = e2.addComponent<BehaviorComponent>();
	bc2->addLogic<FireballLogic>();
	auto ac2 = e2.addComponent<AnimationComponent>();
	ac2->addAnimation("main", std::vector<sf::Vector2f>{
		sf::Vector2f{ 0.0f, 640.0f },
			sf::Vector2f{ 64.0f, 640.0f },
			sf::Vector2f{ 128, 640.0f },
			sf::Vector2f{ 192.0f, 640.0f }},
		5);
	ac2->playAnimation("main", true);

	e2.addTag("fireball");
	e2.addTag("eproj");
	return &e2;
}

Entity* SpawnSystem::buildGrave()
{
	s_entities.push_back(std::make_shared<Entity>());
	Entity& e2 = *s_entities.back();
	auto rc2 = e2.addComponent<RenderComponent>("GFX/Main.png", 0.0f, 0.0f,
		512.0f, 512.0f, 128.0f, 128.0f);
	e2.addTag("grave");
	return &e2;
}