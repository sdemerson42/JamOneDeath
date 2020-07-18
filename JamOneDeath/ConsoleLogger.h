#pragma once

#include "ILogger.h"

class ConsoleLogger : public ILogger
{
	void log(const std::string& msg) const override;
};