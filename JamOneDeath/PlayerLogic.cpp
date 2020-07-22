#include "PlayerLogic.h"
#include "BehaviorComponent.h"
#include "Events.h"
#include "Entity.h"
#include "PhysicsComponent.h"
#include "AnimationComponent.h"
#include "SpawnSystem.h"

PlayerLogic::PlayerLogic(BehaviorComponent* parent) :
	LogicBase{ parent }, m_physics{ parent->parent()->getComponent<PhysicsComponent>() },
	m_animation{ parent->parent()->getComponent<AnimationComponent>() },
	m_renders{ parent->parent()->getComponents<RenderComponent>() },
	m_deathCounter{ 0 }
{
	parent->setCounter("player", 1);
}

void PlayerLogic::execute()
{
	static const float speed = 6.0f;
	static const float acceleration = 0.5f;
	static const float deceleration = 0.5f;

	// State controller

	auto state = parent()->getCounter("state");
	if (state == 1)
	{
		deathCycle();
		return;
	}

	auto velocity = m_physics->velocity();
	
	auto input = parent()->input();

	float x = velocity.x + acceleration * input.moveX;
	if (x > speed) x = speed;
	if (x < -1.0f * speed) x = -1.0f * speed;

	float y = velocity.y + acceleration * input.moveY;
	if (y > speed) y = speed;
	if (y < -1.0f * speed) y = -1.0f * speed;

	m_physics->setVelocity(x, y);

	if (input.moveX == 0.0f && input.moveY == 0.0f)
	{
		m_animation->playAnimation("idle", false);
	}
	else
	{
		m_animation->playAnimation("main", true);
	}

	
}

void PlayerLogic::onCollision(const CollisionEvent& collision)
{
	if (parent()->getCounter("state") == 0)
	{
		if (collision.collider->hasTag("mob"))
		{
			m_physics->setVelocity(0.0f, 0.0f);
			m_renders[1]->setActive(false);
			parent()->setCounter("state", 1);
			m_deathCounter = 0;
			m_animation->playAnimation("poof", false);

			// Logic Swap

			if (parent()->getLogics().size() > 1)
			{
				parent()->removeBackLogic();
			}
			auto newLogic = collision.collider->getComponent<BehaviorComponent>()->
				getLogics()[0]->getLogicCopy();
			newLogic->setParent(parent());
			parent()->addLogicCopy(newLogic);
			parent()->getLogics().back()->playerOpen();
		}
	}
}

void PlayerLogic::deathCycle()
{
	if (m_animation->complete())
	{
		if (m_deathCounter < 55)
		{
			m_renders[0]->setActive(false);
		}
		else
		{
			m_renders[1]->setActive(true);
			parent()->setCounter("state", 0);
		}
	}
	if (++m_deathCounter == 50)
	{
		m_renders[0]->setActive(true);
		m_animation->playAnimation("rpoof", false);
	}
}