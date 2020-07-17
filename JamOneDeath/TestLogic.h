#pragma once

#include "LogicBase.h"
#include "EventHandler.h"

class PhysicsComponent;

class TestLogic : public LogicBase, public EventHandler
{
public:
	TestLogic(BehaviorComponent* parent, float x, float y);
	void execute() override;
private:
	PhysicsComponent* m_pc;
	float m_x;
	float m_y;
	bool m_done = false;
};