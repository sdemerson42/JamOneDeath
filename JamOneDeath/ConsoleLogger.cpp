#include "ConsoleLogger.h"
#include <iostream>

void ConsoleLogger::log(const std::string& msg) const
{
	std::cout << msg << "\n\n";
}