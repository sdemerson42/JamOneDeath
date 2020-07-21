#pragma once
#include "Events.h"

class BehaviorComponent;

class LogicBase
{
public:
	virtual void execute() = 0;
	virtual void onCollision(const CollisionEvent& collision)
	{
		// No default behavior
	}
protected:
	LogicBase(BehaviorComponent* parent);
	BehaviorComponent* parent();
private:
	BehaviorComponent* m_parent;
};
