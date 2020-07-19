#pragma once

#include "LogicBase.h"

class BehaviorComponent;

class DuckShootLogic : public LogicBase
{
public:
	DuckShootLogic(BehaviorComponent* parent);
	void execute() override;
};
