#include "TestLogic.h"
#include <iostream>
#include "BehaviorComponent.h"
#include "Entity.h"
#include "PhysicsComponent.h"

TestLogic::TestLogic(BehaviorComponent* parent, float x, float y) :
	LogicBase{ parent }, m_x {x}, m_y{y},
	m_pc{ parent->parent()->getComponent<PhysicsComponent>() }
{}

void TestLogic::execute()
{
	if (!m_done)
	{
		m_pc->setVelocity(m_x, m_y);
		m_done = true;
	}
}