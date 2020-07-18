#pragma once

#include "ISystem.h"
#include "EventHandler.h"
#include "Events.h"

class InputSystem : public ISystem, public EventHandler
{
public:
	void execute() override;
private:
	InputEvent m_input;
};
