#include "PlayerLogic.h"
#include "BehaviorComponent.h"
#include "Events.h"
#include "Entity.h"
#include "PhysicsComponent.h"
#include "AnimationComponent.h"

InputEvent PlayerLogic::s_input;

PlayerLogic::PlayerLogic(BehaviorComponent* parent) :
	LogicBase{ parent }, m_physics{ parent->parent()->getComponent<PhysicsComponent>() },
	m_animation{ parent->parent()->getComponent<AnimationComponent>() }
{
}

void PlayerLogic::execute()
{
	static const float speed = 6.0f;
	static const float acceleration = 0.5f;
	static const float deceleration = 0.5f;

	auto velocity = m_physics->velocity();
	
	float x = velocity.x + acceleration * s_input.moveX;
	if (x > speed) x = speed;
	if (x < -1.0f * speed) x = -1.0f * speed;

	float y = velocity.y + acceleration * s_input.moveY;
	if (y > speed) y = speed;
	if (y < -1.0f * speed) y = -1.0f * speed;

	m_physics->setVelocity(x, y);

	if (s_input.moveX == 0.0f && s_input.moveY == 0.0f)
	{
		m_animation->playAnimation("idle", false);
	}
	else
	{
		m_animation->playAnimation("main", true);
	}
}

void PlayerLogic::setInput(const InputEvent& event)
{
	s_input = event;
}