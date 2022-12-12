#pragma once
#include "programState.h"

typedef std::unique_ptr<ProgramState> StateReference;

class StateMachine
{
public:
	StateMachine() = default;
	~StateMachine() = default;

	void addNewState(StateReference newState);

	void changingState();
	void deleteState();
	void removeAllStates();

	StateReference& getCurrentState();
	int getNrOfStates() const;

private:
	std::stack<std::unique_ptr<ProgramState>> m_states;
	std::unique_ptr<ProgramState> m_newState;

	int nr_states = 0;
	bool isAdded = false;
	bool isRemoved = false;
};

