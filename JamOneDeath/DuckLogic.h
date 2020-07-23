#pragma once

#include "LogicBase.h"
#include "Events.h"

class BehaviorComponent;

class DuckLogic : public LogicBase
{
public:
	DuckLogic(BehaviorComponent* parent);
	void execute() override;
	void onCollision(const CollisionEvent& collision) override;
	void playerOpen() override;
	void playerClose() override;
	LogicBase* getLogicCopy() override
	{
		return static_cast<LogicBase*>(new DuckLogic{ *this });
	}
private:
	int m_counter = -1;
};