#include "pch.h"
#include "debug.h"

/* --->>> Color codes <<<--- */
const std::string RED = "\033[31m";
const std::string YELLOW = "\033[33m";
const std::string GREEN = "\033[32m";
const std::string RESET = "\033[0m";


/* --->>> Logging <<<--- */
void Debug::Log(std::string message)
{
	if (showLog)
	{
		std::cout << message << std::endl;
	}
}

void Debug::LogWarning(std::string message)
{
	if (showWarning)
	{
		std::cout << YELLOW << message << RESET << std::endl;
	}
}

void Debug::LogError(std::string message)
{
	if (showError)
	{
		std::cout << RED << message << RESET << std::endl;
	}
}

void Debug::LogSuccess(std::string message)
{
	if (showSuccess)
	{
		std::cout << GREEN << message << RESET << std::endl;
	}
}
