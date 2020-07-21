#include "ComponentBase.h"
#include "Entity.h"

ComponentBase::ComponentBase(Entity* parent) :
	m_parent{ parent }, m_active{ false }
{}

Entity* ComponentBase::parent()
{
	return m_parent;
}