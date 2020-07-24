#pragma once

#include "LogicBase.h"

class PhysicsComponent;

class FireballLogic : public LogicBase
{
public:
	FireballLogic(BehaviorComponent* parent);
	void execute() override;
	void onCollision(const CollisionEvent& collision) override;
private:
	PhysicsComponent* m_physics;
};