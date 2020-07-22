#include "GhostLogic.h"
#include "BehaviorComponent.h"
#include "PhysicsComponent.h"
#include "Entity.h"
#include "Logger.h"
#include "SpawnSystem.h"
#include "RenderComponent.h"

GhostLogic::GhostLogic(BehaviorComponent* parent) :
	LogicBase{ parent }
{}

void GhostLogic::execute()
{
	if (parent()->getCounter("player") == 1) return;

	m_counter = ++m_counter % 80;
	if (m_counter == 0)
	{
		auto pc = parent()->parent()->getComponent<PhysicsComponent>();
		pc->setVelocity((float)(rand() % 7 - 3),
			(float)(rand() % 7 - 3));
	}
}

void GhostLogic::onCollision(const CollisionEvent& collision)
{
	if (collision.collider->hasTag("player"))
	{
		SpawnSystem::destroyEntity(parent()->parent()->guid());
	}
}

void GhostLogic::playerOpen()
{
	parent()->parent()->getComponent<PhysicsComponent>()->setSolid(false);
	parent()->parent()->getComponents<RenderComponent>()[1]->setTextureOffset(128.0f, 128.0f);
}

void GhostLogic::playerClose()
{
	parent()->parent()->getComponent<PhysicsComponent>()->setSolid(true);
}