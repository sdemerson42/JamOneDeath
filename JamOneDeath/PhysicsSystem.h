#pragma once

#include "ISystem.h"
#include "EventHandler.h"
#include "Events.h"
#include "SFML/System.hpp"
#include "Entity.h"

class PhysicsComponent;

class PhysicsSystem : public ISystem, public EventHandler
{
public:
	PhysicsSystem();
	void execute() override;
private:
	struct Collision
	{
		PhysicsComponent* a;
		PhysicsComponent* b;
		sf::Vector2f normal;
	};

	SetTilemapEvent m_tilemapData;
	Entity m_tileCollider;

	void resolveEntityCollisions();
	bool detectCollision(Collision* c);
	void resolveTilemapCollisions();
	bool tileOverlap(PhysicsComponent* pc);

	void onSetTilemap(const SetTilemapEvent* event);
};