#include <iostream>
#include <stdexcept>
#include "Controller.h"
#include "Logger.h"

int main() try
{
	Controller controller;
	controller.run();
}
catch (const std::exception& e)
{
	Logger::getInstance().logError(e.what());
}