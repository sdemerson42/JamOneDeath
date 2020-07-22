#pragma once

#include "LogicBase.h"
#include "Events.h"

class BehaviorComponent;

class GhostLogic : public LogicBase
{
public:
	GhostLogic(BehaviorComponent* parent);
	void execute() override;
	void onCollision(const CollisionEvent& collision) override;
	void playerOpen() override;
	void playerClose() override;
	LogicBase* getLogicCopy() override
	{
		return static_cast<LogicBase*>(new GhostLogic{ *this });
	}
private:
	int m_counter = -1;
};