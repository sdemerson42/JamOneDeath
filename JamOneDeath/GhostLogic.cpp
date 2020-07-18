#include "GhostLogic.h"
#include "BehaviorComponent.h"
#include "PhysicsComponent.h"
#include "Entity.h"

GhostLogic::GhostLogic(BehaviorComponent* parent) :
	LogicBase{ parent }
{}

void GhostLogic::execute()
{
	m_counter = ++m_counter % 80;
	if (m_counter == 0)
	{
		auto pc = parent()->parent()->getComponent<PhysicsComponent>();
		pc->setVelocity((float)(rand() % 7 - 3),
			(float)(rand() % 7 - 3));
	}
}