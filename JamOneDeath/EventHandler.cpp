#include "EventHandler.h"

void EventHandler::broadcastEvent(const EventBase* event)
{
	auto sz = AutoList<EventHandler>::size();
	for (int i = 0; i < sz; ++i)
	{
		auto handler = AutoList<EventHandler>::get(i);
		if (handler != this) handler->handleEvent(event);
	}
}

void EventHandler::handleEvent(const EventBase* event)
{
	auto pair = m_delegateMap.find(std::type_index{ typeid(*event) });
	if (pair != std::end(m_delegateMap)) pair->second->call(event);
}