#pragma once

#include "ISystem.h"
#include "EventHandler.h"

class InputSystem : public ISystem, public EventHandler
{
public:
	void execute() override;
};
