#pragma once

#include "LogicBase.h"
#include "Events.h"
#include <vector>
#include "RenderComponent.h"
#include <string>

class BehaviorComponent;
class PhysicsComponent;
class AnimationComponent;

class PlayerLogic : public LogicBase
{
public:
	PlayerLogic(BehaviorComponent* parent);
	void execute() override;
	void onCollision(const CollisionEvent& collision) override;
private:
	PhysicsComponent* m_physics;
	AnimationComponent* m_animation;
	std::vector<RenderComponent*> m_renders;
	
	void deathCycle();

	int m_deathCounter;
	std::string m_reincarnationTag;
};