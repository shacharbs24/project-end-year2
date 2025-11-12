#include "Logger.h"
#include <fstream>
#include <iostream>

Logger& Logger::getInstance()
{
	static Logger instance;
	return instance;
}

void Logger::logError(std::string errorMessage)
{
	writeToFile(std::move(errorMessage));
}

void Logger::writeToFile(const std::string& errorMessage)
{
	std::ofstream file("error.log", std::ios_base::app);
	if (file)
	{
		file << errorMessage << std::endl;
	}
}