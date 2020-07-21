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
	
	template<typename ...Args>
	static void buildEntity(const std::string& name, Args ...args)
	{
		if (name == "Natty") buildNatty(args...);
		if (name == "Ghost") buildGhost(args...);
	}

	static void destroyEntity(unsigned int guid)
	{
		s_guids.push_back(guid);
	}
private:
	static std::vector<std::shared_ptr<Entity>> s_entities;
	static std::vector<unsigned int> s_guids;
	static std::vector<std::shared_ptr<Entity>>* s_simEntities;

    static void buildNatty(float posX, float posY);
	static void buildGhost(float posX, float posY);
};
