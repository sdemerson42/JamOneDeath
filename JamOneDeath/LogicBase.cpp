#include "LogicBase.h"
#include "BehaviorComponent.h"

LogicBase::LogicBase(BehaviorComponent* parent) :
	m_parent{ parent }
{}

BehaviorComponent* LogicBase::parent()
{
	return m_parent;
}

void LogicBase::setParent(BehaviorComponent* parent)
{
	m_parent = parent;
}