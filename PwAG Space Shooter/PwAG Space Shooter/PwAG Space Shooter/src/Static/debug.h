#pragma once
#include <string>
#include <iostream>

class Debug
{
public:
	Debug() = delete;

	static void Log(std::string message);
	static void LogWarning(std::string message);
	static void LogError(std::string message);
	static void LogSuccess(std::string message);

	static const bool showLog = true;
	static const bool showWarning = true;
	static const bool showError = true;
	static const bool showSuccess = true;
};
