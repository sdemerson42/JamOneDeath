#pragma once

#include <memory>
#include <vector>
#include "Entity.h"
#include "ISystem.h"
#include "EventHandler.h"
#include <string>

class SpawnSystem : public ISystem, public EventHandler
{
public:
	SpawnSystem(std::vector<std::shared_ptr<Entity>>* simEntities)
	{
		s_simEntities = simEntities;
	}
	void execute() override;
	
	static Entity* buildEntity(const std::string& name, float posX, float posY)
	{
		Entity* r = nullptr;
		if (name == "Natty") r = buildNatty();
		else if (name == "Ghost") r = buildGhost();
		else if (name == "Duck") r = buildDuck();
		else if (name == "Fireball") r = buildFireball();

		if (r) r->setPosition(posX, posY);

		return r;
	}

	static void destroyEntity(unsigned int guid)
	{
		s_guids.push_back(guid);
	}
private:
	static std::vector<std::shared_ptr<Entity>> s_entities;
	static std::vector<unsigned int> s_guids;
	static std::vector<std::shared_ptr<Entity>>* s_simEntities;

    static Entity* buildNatty();
	static Entity* buildGhost();
	static Entity* buildDuck();
	static Entity* buildFireball();
};
