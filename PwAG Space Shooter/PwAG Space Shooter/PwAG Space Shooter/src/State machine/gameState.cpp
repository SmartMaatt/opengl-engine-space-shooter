#include "pch.h"
#include "gameState.h"

GameState::GameState(GameReference gameReference)
{
	this->gameReference = gameReference;
}

GameState::~GameState() {}

void GameState::initialization()
{
	this->spaceLevel = new Maze();
	glfwSetInputMode(this->gameReference->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	this->cursorDisabled = true;
}

void GameState::processInput(float deltaTime, Keyboard& keyboard, Mouse& mouse)
{
	this->spaceLevel->camera->updateInput(gameReference, keyboard, mouse, deltaTime);

	if (keyboard.keyState[static_cast<int>(Keyboard::Key::eKeyEscape)]) 
	{
		if (this->cursorDisabled) 
		{
			glfwSetInputMode(this->gameReference->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			this->cursorDisabled = false;
		} 
		else 
		{
			glfwSetInputMode(this->gameReference->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			this->cursorDisabled = true;
		}
	}
}

void GameState::update(float deltaTime)
{
	this->spaceLevel->updateMaze(deltaTime);
}

void GameState::render(float deltaTime, bool wireframe)
{
	this->spaceLevel->drawMaze(deltaTime, wireframe);
}