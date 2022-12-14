#include "pch.h"
#include "gameState.h"

GameState::GameState(GameReference gameReference)
{
	this->gameReference = gameReference;
}

GameState::~GameState() {}

void GameState::initialization()
{
	this->spaceLevel = new SpaceLevel();
	glfwSetInputMode(this->gameReference->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	this->cursorDisabled = true;
}

void GameState::processInput(float deltaTime, Keyboard& keyboard, Mouse& mouse)
{
	this->spaceLevel->player->updateInput(gameReference, keyboard, mouse, deltaTime);

	// Shooting
	if (keyboard.keyState[static_cast<int>(Keyboard::Key::eKeyF)])
	{
		this->spaceLevel->shootBullet();
	}
}

void GameState::update(float deltaTime)
{
	this->spaceLevel->updateLevel(deltaTime);
}

void GameState::render(float deltaTime, bool wireframe)
{
	this->spaceLevel->drawLevel(deltaTime, wireframe);
}