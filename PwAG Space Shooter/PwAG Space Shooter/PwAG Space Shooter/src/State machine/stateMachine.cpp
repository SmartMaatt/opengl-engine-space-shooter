#include "pch.h"
#include "stateMachine.h"

void StateMachine::removeAllStates()
{
	while (!m_states.empty())
	{
		m_states.pop();
	}
}

StateReference& StateMachine::getCurrentState()
{
	return this->m_states.top();
}

void StateMachine::addNewState(StateReference newState)
{
	this->isAdded = true;
	this->m_newState = std::move(newState);
}

void StateMachine::changingState()
{
	if ((this->isRemoved == true) && !this->m_states.empty())
	{
		this->m_states.pop();
		this->isRemoved = false;
		this->nr_states--;
	}
	if (this->isAdded == true)
	{
		if (!this->m_states.empty())
		{
			this->m_states.pop();
			this->nr_states--;
		}
		this->m_states.push(std::move(this->m_newState));
		this->m_states.top()->initialization(); 
		this->isAdded = false;
		this->nr_states++;
	}
}

void StateMachine::deleteState()
{
	this->isRemoved = true;
}


int StateMachine::getNrOfStates() const
{
	return this->nr_states; 
}
