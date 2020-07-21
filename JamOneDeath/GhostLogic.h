#pragma once

#include "LogicBase.h"
#include "EventHandler.h"
#include "Events.h"

class BehaviorComponent;

class GhostLogic : public LogicBase, public EventHandler
{
public:
	GhostLogic(BehaviorComponent* parent);
	void execute() override;
	void onCollision(const CollisionEvent& collision) override;
private:
	int m_counter = -1;
};