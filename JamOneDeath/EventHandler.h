#pragma once

#include "EventBase.h"
#include "AutoList.h"

#include <memory>
#include <map>
#include <typeindex>

template<typename T, typename EventT>
using MFunc = void(T::*)(const EventT*);

class IDelegate
{
public:
	virtual void call(const EventBase* event) = 0;
};

template<typename T, typename EventT>
class Delegate : public IDelegate
{
public:
	Delegate(T *object, MFunc<T, EventT> func) :
		m_object{ object }, m_func{ func }
	{}
	void call(const EventBase* event) override
	{
		(m_object->*m_func)(static_cast<const EventT*>(event));
	}
private:
	T* m_object;
	MFunc<T, EventT> m_func;
};

class EventHandler : public AutoList<EventHandler>
{
public:
	template<typename T, typename EventT>
	void registerFunc(T* object, MFunc<T, EventT> func)
	{
		m_delegateMap[std::type_index{ typeid(EventT) }] =
			std::make_unique<Delegate<T, EventT>>(object, func);
	}
	void broadcastEvent(const EventBase* event);
	void handleEvent(const EventBase* event);
private:
	std::map<std::type_index, std::unique_ptr<IDelegate>> m_delegateMap;
};