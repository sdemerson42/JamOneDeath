#pragma once

class BehaviorComponent;

class LogicBase
{
public:
	virtual void execute() = 0;
protected:
	LogicBase(BehaviorComponent* parent);
	BehaviorComponent* parent();
private:
	BehaviorComponent* m_parent;
};
