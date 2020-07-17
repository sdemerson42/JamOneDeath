#pragma once

#include "LogicBase.h"
#include "EventHandler.h"
#include "Events.h"

class BehaviorComponent;
class PhysicsComponent;

class PlayerLogic : public LogicBase, public EventHandler
{
public:
	PlayerLogic(BehaviorComponent* parent);
	void execute() override;
	static void setInput(const InputEvent& event);
private:
	static InputEvent m_input;
	PhysicsComponent* m_physics;
};