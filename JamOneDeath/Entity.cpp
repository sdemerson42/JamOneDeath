#include "Entity.h"

unsigned int Entity::s_guidCounter = 0;

Entity::Entity() :
	m_guid{ s_guidCounter++ }, m_active{ true }
{
}