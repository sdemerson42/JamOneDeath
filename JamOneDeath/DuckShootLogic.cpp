#include "DuckShootLogic.h"
#include "Logger.h"
#include "BehaviorComponent.h"

DuckShootLogic::DuckShootLogic(BehaviorComponent* parent) :
	LogicBase{ parent }
{}

void DuckShootLogic::execute()
{
	auto val = parent()->getCounter("test");
	val = ++val % 60;
	if (val == 0) Logger::log("Bang!");
	parent()->setCounter("test", val);
}