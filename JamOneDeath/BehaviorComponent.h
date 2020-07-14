#pragma once

#include "ComponentBase.h"
#include "EventHandler.h"
#include "AutoList.h"
#include <memory>
#include "LogicBase.h"

class BehaviorComponent : public ComponentBase, public EventHandler, 
	public AutoList<BehaviorComponent>
{
public:
	BehaviorComponent(Entity* parent) :
		ComponentBase{ parent }
	{
	}
	template<typename T>
	void addLogic()
	{
		m_logic = std::make_unique<T>(this);
	}
	LogicBase* logic()
	{
		return m_logic.get();
	}
private:
	std::unique_ptr<LogicBase> m_logic;
};