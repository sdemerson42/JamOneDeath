#include <memory>
#include "Sim.h"
#include <time.h>

int main()
{
	srand(time(NULL));

	std::unique_ptr<Sim> sim{ std::make_unique<Sim>() };
	sim->execute();

	return 0;
}