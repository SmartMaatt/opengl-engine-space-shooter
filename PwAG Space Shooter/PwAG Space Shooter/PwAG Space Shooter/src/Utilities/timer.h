#pragma once

class Timer
{
public:
	// Constructors / Destructor
	Timer() = default;
	Timer(const Timer&) = delete;

	// Operators
	Timer& operator=(const Timer&) = delete;

	// Timers
	void startTimer(const std::string& name);
	void stopTimer(const std::string& name);

	// Getters
	double getCurrentDurationInSeconds(const std::string& name) const;
	double getCurrentDurationInMiliseconds(const std::string& name) const;
	double getCurrentDurationInMicroseconds(const std::string& name) const;
	double getCurrentDurationInNanoseconds(const std::string& name) const;

	double getMeasuredDurationInSeconds(const std::string& name) const;
	double getMeasuredDurationInMiliseconds(const std::string& name) const;
	double getMeasuredDurationInMicroseconds(const std::string& name) const;
	double getMeasuredDurationInNanoseconds(const std::string& name) const;

private:
	std::unordered_map<std::string, std::chrono::steady_clock::time_point> _start;
	std::unordered_map<std::string, std::chrono::steady_clock::time_point> _stop;
};

