#pragma once
#include "stateMachine.h"

struct GameAssets
{
	GLFWwindow* window;
	StateMachine m_stateMachine; //state machine
};

typedef	std::shared_ptr<GameAssets> GameReference;
