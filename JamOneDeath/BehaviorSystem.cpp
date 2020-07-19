#include "BehaviorSystem.h"
#include "BehaviorComponent.h"

void BehaviorSystem::execute()
{
	auto size = AutoList<BehaviorComponent>::size();
	for (int i = 0; i < size; ++i)
	{
		auto bc = AutoList<BehaviorComponent>::get(i);
		for (int i = 0; i < bc->getLogics().size(); ++i)
		{
			auto& sp = bc->getLogics()[i];
			sp->execute();
		}
	}
}