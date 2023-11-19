#pragma once
#include "programState.h"

typedef std::unique_ptr<ProgramState> StateReference;

class StateMachine
{
public:
	// Constructors / Destructor
	StateMachine() = default;
	~StateMachine() = default;

	// States
	void addNewState(StateReference newState);
	void changingState();
	void deleteState();
	void removeAllStates();

	// Getters
	StateReference& getCurrentState();
	int getNrOfStates() const;

private:
	// States
	std::stack<std::unique_ptr<ProgramState>> _states;
	std::unique_ptr<ProgramState> _newState;

	// Parameters
	int _nrStates = 0;
	bool _isAdded = false;
	bool _isRemoved = false;
};