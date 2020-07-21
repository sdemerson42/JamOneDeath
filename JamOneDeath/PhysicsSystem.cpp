#include "PhysicsSystem.h"
#include "PhysicsComponent.h"
#include "Entity.h"
#include "Globals.h"
#include <algorithm>
#include "Logger.h"
#include "Events.h"
#include "BehaviorComponent.h"
#include "LogicBase.h"

PhysicsSystem::PhysicsSystem()
{
	registerFunc(this, &PhysicsSystem::onSetTilemap);
}

void PhysicsSystem::execute()
{
	resolveEntityCollisions();
	resolveTilemapCollisions();
}

void PhysicsSystem::resolveEntityCollisions()
{
	auto size = AutoList<PhysicsComponent>::size();
	Collision c;
	for (int i = 0; i < size; ++i)
	{
		c.a = AutoList<PhysicsComponent>::get(i);
		if (!c.a->active()) continue;
		for (int j = i + 1; j < size; ++j)
		{
			c.b = AutoList<PhysicsComponent>::get(j);
			if (!c.b->active()) continue;
			
			if (detectCollision(&c))
			{
				if (c.a->solid() && c.b->solid())
				{
					// Resolve collision by changing velocities of colliding objects.

					// Restitution will be 1.0f by default.
					const float e = 1.0f;

					auto relativeVelocity = c.b->velocity() - c.a->velocity();
					float rvAlongNormal = relativeVelocity.x * c.normal.x +
						relativeVelocity.y * c.normal.y;

					// Only resolve physical collision if in a collision vector

					if (rvAlongNormal < 0.0f)
					{
						float impulseMagnitude = (-1.0f * (e + 1.0f) * rvAlongNormal) /
							(c.a->inverseMass() + c.b->inverseMass());

						auto av = c.a->velocity();
						auto bv = c.b->velocity();

						auto apv = av - (impulseMagnitude * c.normal) / c.a->mass();
						c.a->setVelocity(apv.x, apv.y);
						auto bpv = bv + (impulseMagnitude * c.normal) / c.b->mass();
						c.b->setVelocity(bpv.x, bpv.y);
					}
				}

				// Inform Logics of collision if they exist
				auto abc = c.a->parent()->getComponent<BehaviorComponent>();
				if (abc)
				{
					auto alogics = abc->getLogics();
					for (auto& sp : alogics)
					{
						CollisionEvent ce;
						ce.collider = c.b->parent();
						sp->onCollision(ce);
					}
				}

				auto bbc = c.b->parent()->getComponent<BehaviorComponent>();
				if (bbc)
				{
					auto blogics = bbc->getLogics();
					for (auto& sp : blogics)
					{
						CollisionEvent ce;
						ce.collider = c.a->parent();
						sp->onCollision(ce);
					}
				}
			}
		}
	}
}

bool PhysicsSystem::detectCollision(Collision* c)
{
	if (!c->a->active() || !c->b->active()) return false;

	sf::Vector2f extent;
	extent.x = (c->b->parent()->position().x +
		c->b->colliderOffset().x +
		c->b->colliderSize().x / 2.0f) -
		(c->a->parent()->position().x +
			c->a->colliderOffset().x +
			c->a->colliderSize().x / 2.0f);
	extent.y = (c->b->parent()->position().y +
		c->b->colliderOffset().y +
		c->b->colliderSize().y / 2.0f) -
		(c->a->parent()->position().y +
			c->a->colliderOffset().y +
			c->a->colliderSize().y / 2.0f);

	float xOverlap = (c->a->colliderSize().x / 2.0f +
		c->b->colliderSize().x / 2.0f) -
		abs(extent.x);
	if (xOverlap > 0.0f)
	{
		float yOverlap = (c->a->colliderSize().y / 2.0f +
			c->b->colliderSize().y / 2.0f) -
			abs(extent.y);
		if (yOverlap > 0.0f)
		{
			// Collision detected
			if (xOverlap < yOverlap)
			{
				if (extent.x < 0.0f) c->normal.x = -1.0f;
				else c->normal.x = 1.0f;
			}
			else
			{
				if (extent.y < 0.0f) c->normal.y = -1.0f;
				else c->normal.y = 1.0f;
			}
			return true;
		}
	}
	return false;
}

void PhysicsSystem::resolveTilemapCollisions()
{
	auto size = AutoList<PhysicsComponent>::size();
	for (int i = 0; i < size; ++i)
	{
		auto pc = AutoList<PhysicsComponent>::get(i);
		if (!pc->active()) continue;

		// Resolve tilemap collisions direction by direction

		// Dirty positioning... fix later
		auto oldPosition = pc->parent()->position();
		pc->parent()->addPosition(pc->velocity().x, 0.0f);
		if (tileOverlap(pc))
		{
			pc->parent()->setPosition(oldPosition);
			pc->setVelocity(0.0f, pc->velocity().y);
		}
		
		pc->parent()->addPosition(0.0f, pc->velocity().y);
		if (tileOverlap(pc))
		{
			pc->parent()->setPosition(pc->parent()->position().x,
				oldPosition.y);
			pc->setVelocity(pc->velocity().x, 0.0f);
		}
	}
}

bool PhysicsSystem::tileOverlap(PhysicsComponent *pc)
{
	auto pos = pc->parent()->position() + pc->colliderOffset();
	auto cSize = pc->colliderSize();
	float leftPos = pos.x;
	float rightPos = pos.x + cSize.x;
	float topPos = pos.y;
	float bottomPos = pos.y + cSize.y;

	int leftTile = std::max(0,(int)leftPos / Globals::tileWidth);
	int rightTile = std::min(Globals::tilemapWidth - 1, 
		(int)rightPos / Globals::tileWidth);
	int topTile = std::max(0, (int)topPos / Globals::tileHeight);
	int bottomTile = std::min(Globals::tilemapHeight - 1,
		(int)bottomPos / Globals::tileHeight);

	for (int j = topTile; j <= bottomTile; ++j)
	{
		for (int i = leftTile; i <= rightTile; ++i)
		{
			int testTile = (*m_tilemapData.tilemap)[i][j];
			if (std::find(std::begin(*m_tilemapData.blockedTiles),
				std::end(*m_tilemapData.blockedTiles), testTile) !=
				std::end(*m_tilemapData.blockedTiles))
			{
				return true;
			}
		}
	}
	return false;
}

void PhysicsSystem::onSetTilemap(const SetTilemapEvent* event)
{
	m_tilemapData = *event;
}