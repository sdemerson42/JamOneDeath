#include "GhostLogic.h"
#include "BehaviorComponent.h"
#include "PhysicsComponent.h"
#include "Entity.h"
#include "Logger.h"
#include "SpawnSystem.h"
#include "RenderComponent.h"

GhostLogic::GhostLogic(BehaviorComponent* parent) :
	LogicBase{ parent }, m_target{ nullptr }
{}

void GhostLogic::execute()
{
	if (parent()->getCounter("player") == 1) return;

	auto pc = parent()->parent()->getComponent<PhysicsComponent>();
	float x = m_target->position().x - parent()->parent()->position().x;
	float y = m_target->position().y - parent()->parent()->position().y;
	float speed = 1.5f;
	float magnitude = sqrt(x * x + y * y);
	pc->setVelocity(x / magnitude * speed, y / magnitude * speed);
	
	
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

void GhostLogic::setTarget(Entity* target)
{
	m_target = target;
}