#pragma once

#include "LogicBase.h"
#include "EventHandler.h"
#include "Events.h"
#include <vector>
#include "RenderComponent.h"

class BehaviorComponent;
class PhysicsComponent;
class AnimationComponent;

class PlayerLogic : public LogicBase, public EventHandler
{
public:
	PlayerLogic(BehaviorComponent* parent);
	void execute() override;
	static void setInput(const InputEvent& event);
private:
	static InputEvent s_input;
	PhysicsComponent* m_physics;
	AnimationComponent* m_animation;
	std::vector<RenderComponent*> m_renders;
	int m_hatIndex = 0;
};