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

		switch (roll)
		{
		case 0:
			x = -2.0f;
			break;
		case 1:
			x = 2.0f;
			break;
		case 2:
			y = -2.0f;
			break;
		case 3:
			y = 2.0f;
			break;
		}

		pc->setVelocity(x, y);
	}
}

void DuckLogic::onCollision(const CollisionEvent& collision)
{
	if (collision.collider->hasTag("player"))
	{
		SpawnSystem::destroyEntity(parent()->parent()->guid());
	}
}

void DuckLogic::playerOpen()
{
	parent()->parent()->getComponents<RenderComponent>()[1]->setTextureOffset(256.0f, 128.0f);
	
}

void DuckLogic::playerClose()
{
	
}