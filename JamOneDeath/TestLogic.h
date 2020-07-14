#pragma once

#include "LogicBase.h"
#include "EventHandler.h"

class TestLogic : public LogicBase, public EventHandler
{
public:
	TestLogic(BehaviorComponent* parent);
	void execute() override;
};