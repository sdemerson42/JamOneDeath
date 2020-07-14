#pragma once

#include "ISystem.h"
#include "EventHandler.h"

class BehaviorSystem : public ISystem, public EventHandler
{
public:
	void execute() override;
};