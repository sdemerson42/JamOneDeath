#include "Logger.h"
#include "ConsoleLogger.h"

std::unique_ptr<ILogger> Logger::m_logger{
	std::make_unique<ConsoleLogger>() };

void Logger::log(const std::string& msg)
{
	m_logger->log(msg);
}