#include <memory>
#include "Sim.h"

int main()
{
	std::unique_ptr<Sim> sim{ std::make_unique<Sim>() };
	sim->execute();

	return 0;
}