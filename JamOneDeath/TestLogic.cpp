#include "TestLogic.h"
#include <iostream>
#include "BehaviorComponent.h"
#include "Entity.h"

TestLogic::TestLogic(BehaviorComponent* parent) :
	LogicBase{ parent }
{}

void TestLogic::execute()
{
	parent()->parent()->addPosition(0.1f, 0.0f);
	std::cout << parent()->parent()->position().x;
}