#pragma once
#include "stateMachine.h"

struct GameAssets
{
	GLFWwindow* window;				// Window object
	StateMachine _stateMachine;	// State machine
};

typedef	std::shared_ptr<GameAssets> GameReference;