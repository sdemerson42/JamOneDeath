#pragma once

#include <memory>
#include "ILogger.h"

class Logger
{
public:
	static void log(const std::string& msg);
private:
	static std::unique_ptr<ILogger> m_logger;
};