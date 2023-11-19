#include "pch.h"
#include "stateMachine.h"

/* --->>> States <<<--- */
void StateMachine::addNewState(StateReference newState)
{
	_isAdded = true;
	_newState = std::move(newState);
}

void StateMachine::changingState()
{
	if ((_isRemoved == true) && !_states.empty())
	{
		_states.pop();
		_isRemoved = false;
		_nrStates--;
	}

	if (_isAdded == true)
	{
		if (!_states.empty())
		{
			_states.pop();
			_nrStates--;
		}
		_states.push(std::move(_newState));
		_states.top()->initialization();
		_isAdded = false;
		_nrStates++;
	}
}

void StateMachine::deleteState()
{
	_isRemoved = true;
}

void StateMachine::removeAllStates()
{
	while (!_states.empty())
	{
		_states.pop();
	}
}


/* --->>> Getters <<<--- */
StateReference& StateMachine::getCurrentState()
{
	return _states.top();
}

int StateMachine::getNrOfStates() const
{
	return _nrStates;
}
