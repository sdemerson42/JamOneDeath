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
	virtual void playerOpen()
	{
		// No default behavior

	}
	virtual void playerClose()
	{
		// No default behavior

	}
	virtual LogicBase* getLogicCopy()
	{
		return nullptr;
	}
	BehaviorComponent* parent();
	void setParent(BehaviorComponent* parent);
protected:
	LogicBase(BehaviorComponent* parent);
private:
	BehaviorComponent* m_parent;
};
