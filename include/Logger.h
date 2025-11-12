#pragma once
#include <string>

class Logger
{
public:
	static Logger& getInstance();
	void logError(std::string errorMessage);

private:
	Logger() = default;
	~Logger() = default;
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;
	Logger(Logger&&) = delete;
	Logger& operator=(Logger&&) = delete;

	void writeToFile(const std::string& errorMessage);
};