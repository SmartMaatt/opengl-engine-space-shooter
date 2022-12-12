#include "pch.h"
#include "gameState.h"

GameState::GameState(GameReference gameReference)
{
	this->gameReference = gameReference;
}

GameState::~GameState()
{
}

void GameState::initialization()
{
	this->maze = new Maze();
	glfwSetInputMode(this->gameReference->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	this->cursorDisabled = true;
}

void GameState::processInput(float deltaTime, Keyboard& keyboard, Mouse& mouse)
{
	this->maze->camera->updateInput(gameReference, keyboard, mouse, deltaTime);

	/*if (this->maze->willBeCollisionWithExit()) {
		this->gameReference->m_stateMachine.addNewState(StateReference(new GameOverState(this->gameReference)));
	}*/

	/*if (this->maze->willBeCollisionWithWall(deltaTime)) {
		this->maze->camera->revertCameraPosition();
	}
	else {
		this->maze->camera->updateCameraPosition();
	}*/

	if (keyboard.keyState[static_cast<int>(Keyboard::Key::eKeyEscape)]) {
		if (this->cursorDisabled) {
			glfwSetInputMode(this->gameReference->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			this->cursorDisabled = false;
		} else {
			glfwSetInputMode(this->gameReference->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			this->cursorDisabled = true;
		}
	}
}

void GameState::update(float deltaTime)
{
	this->maze->updateMaze(deltaTime);
}

void GameState::render(float deltaTime, bool wireframe)
{
	this->maze->drawMaze(deltaTime, wireframe);
}
