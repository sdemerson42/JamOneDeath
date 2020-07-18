#pragma once

#include "LogicBase.h"
#include "EventHandler.h"

class BehaviorComponent;

class GhostLogic : public LogicBase, public EventHandler
{
public:
	GhostLogic(BehaviorComponent* parent);
	void execute() override;
private:
	int m_counter = -1;
};