#include "DuckLogic.h"
#include "BehaviorComponent.h"
#include "PhysicsComponent.h"
#include "Entity.h"
#include "Logger.h"
#include "SpawnSystem.h"
#include "RenderComponent.h"

DuckLogic::DuckLogic(BehaviorComponent* parent) :
	LogicBase{ parent }
{}

void DuckLogic::execute()
{
	if (parent()->getCounter("player") == 1) return;

	m_counter = ++m_counter % 45;
	if (m_counter == 0)
	{
		auto pc = parent()->parent()->getComponent<PhysicsComponent>();
		auto roll = rand() % 4;
		float x = 0.0f;
		float y = 0.0f;
		float fx = 0.0f;
		float fy = 0.0f;
		auto position = parent()->parent()->position();
		position.x += 32.0f;
		position.y += 32.0f;

		switch (roll)
		{
		case 0:
			x = -2.0f;
			fy = -6.0f;
			position.y -= 64.0f;
			break;
		case 1:
			x = 2.0f;
			fy = 6.0f;
			position.y += 90.0f;
			break;
		case 2:
			y = -2.0f;
			fx = 6.0f;
			position.x += 64.0f;
			break;
		case 3:
			y = 2.0f;
			fx = -6.0f;
			position.x -= 64.0f;
			break;
		}

		pc->setVelocity(x, y);
		auto fb = SpawnSystem::buildEntity("Fireball", position.x, position.y);
		fb->getComponent<PhysicsComponent>()->setVelocity(fx, fy);
	}
}

void DuckLogic::onCollision(const CollisionEvent& collision)
{
	if (collision.collider->hasTag("player"))
	{
		SpawnSystem::destroyEntity(parent()->parent()->guid());
	}
	else if (collision.collider->hasTag("tile"))
	{
		m_counter = -1;
	}
}

void DuckLogic::playerOpen()
{
	parent()->parent()->getComponents<RenderComponent>()[1]->setTextureOffset(256.0f, 128.0f);
	
}

void DuckLogic::playerClose()
{
	
}