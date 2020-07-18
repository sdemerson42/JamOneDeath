#pragma once

#include "EventHandler.h"
#include "ISystem.h"

class AnimationSystem : public ISystem, public EventHandler
{
public:
	void execute() override;
};