#include "AnimationSystem.h"
#include "AnimationComponent.h"

void AnimationSystem::execute()
{
	auto size = AutoList<AnimationComponent>::size();
	for (int i = 0; i < size; ++i)
	{
		auto ac = AutoList<AnimationComponent>::get(i);
		if (ac->active())
		{
			ac->tick();
		}
	}
}