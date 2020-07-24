#include "FireballLogic.h"
#include "PhysicsComponent.h"
#include "BehaviorComponent.h"
#include "Entity.h"
#include "SpawnSystem.h"

FireballLogic::FireballLogic(BehaviorComponent* parent) :
	LogicBase{ parent }, m_physics{ parent->parent()->getComponent<PhysicsComponent>() }
{
}

void FireballLogic::execute()
{

}

void FireballLogic::onCollision(const CollisionEvent& collision)
{
	SpawnSystem::destroyEntity(parent()->parent()->guid());
}