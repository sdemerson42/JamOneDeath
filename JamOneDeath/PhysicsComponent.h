#pragma once

#include "EventHandler.h"
#include "AutoList.h"
#include "ComponentBase.h"
#include "SFML/System.hpp"

class PhysicsComponent : public EventHandler, public ComponentBase,
	public AutoList<PhysicsComponent>
{
public:
	PhysicsComponent(Entity* parent, bool solid, float offsetX, float offsetY,
		float sizeX, float sizeY, float mass) :
		ComponentBase{ parent }, m_solid{ solid }, m_colliderOffset{ offsetX, offsetY },
		m_colliderSize{ sizeX, sizeY }, m_mass{ mass }
	{}

	bool solid() const
	{
		return m_solid;
	}
	void setSolid(bool value)
	{
		m_solid = value;
	}

	const sf::Vector2f& colliderOffset() const
	{
		return m_colliderOffset;
	}
	void setColliderOffset(float x, float y)
	{
		m_colliderOffset.x = x;
		m_colliderOffset.y = y;
	}

	const sf::Vector2f& colliderSize() const
	{
		return m_colliderSize;
	}
	void setColliderSize(float x, float y)
	{
		m_colliderSize.x = x;
		m_colliderSize.y = y;
	}

	const sf::Vector2f& velocity() const
	{
		return m_velocity;
	}
	void setVelocity(float x, float y)
	{
		m_velocity.x = x;
		m_velocity.y = y;
	}
	void addVelocity(float x, float y)
	{
		m_velocity.x += x;
		m_velocity.y += y;
	}

	float mass() const
	{
		return m_mass;
	}
	float inverseMass() const
	{
		return m_mass == 0.0f ? 0.0f : 1.0f / m_mass;
	}
private:
	bool m_solid;
	sf::Vector2f m_colliderOffset;
	sf::Vector2f m_colliderSize;
	sf::Vector2f m_velocity;
	float m_mass;
};