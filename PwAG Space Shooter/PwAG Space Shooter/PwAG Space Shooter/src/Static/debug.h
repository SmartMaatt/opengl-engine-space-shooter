#pragma once
#include <string>
#include <iostream>

class Debug
{
public:
	// Constructors / Destructor
	Debug() = delete;

	// Logging
	static void Log(std::string message);
	static void LogWarning(std::string message);
	static void LogError(std::string message);
	static void LogSuccess(std::string message);

	// Parameters
	static const bool showLog = true;
	static const bool showWarning = true;
	static const bool showError = true;
	static const bool showSuccess = true;
};
