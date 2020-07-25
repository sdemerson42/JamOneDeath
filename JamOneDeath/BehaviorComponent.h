#pragma once

#include "ComponentBase.h"
#include "EventHandler.h"
#include "AutoList.h"
#include <memory>
#include "LogicBase.h"
#include "Events.h"
#include <vector>
#include <map>
#include <string>

class BehaviorComponent : public ComponentBase, public EventHandler, 
	public AutoList<BehaviorComponent>
{
public:
	BehaviorComponent(Entity* parent) :
		ComponentBase{ parent }
	{
	}
	template<typename T, typename ...Args>
	T* addLogic(Args ...args)
	{
		m_logics.push_back(std::make_shared<T>(this, args...));
		return static_cast<T*>(m_logics.back().get());
	}

	void addLogicCopy(LogicBase* copy)
	{
		m_logics.push_back(std::shared_ptr<LogicBase>(copy));
	}

	const std::vector<std::shared_ptr<LogicBase>>& getLogics()
	{
		return m_logics;
	}

	void removeBackLogic()
	{
		if (m_logics.size() > 0)
			m_logics.erase(std::rbegin(m_logics).base() - 1);
	}

	void setCounter(const std::string& name, int value)
	{
		m_counters[name] = value;
	}
	int addCounter(const std::string& name, int value)
	{
		auto& pr = m_counters[name];
		pr += value;
		return pr;
	}
	int getCounter(const std::string& name)
	{
		return m_counters[name];
	}
	static void setInput(const InputEvent& event)
	{
		s_input = event;
	}
	static const InputEvent& input()
	{
		return s_input;
	}
private:
	std::vector<std::shared_ptr<LogicBase>> m_logics;
	std::map<std::string, int> m_counters;
	static InputEvent s_input;
};