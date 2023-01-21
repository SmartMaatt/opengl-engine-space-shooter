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

	// Activating HUD
	if (keyboard.keyState[static_cast<int>(Keyboard::Key::eKeyH)])
	{
		this->spaceLevel->ToggleHUD();
	}
}

void GameState::update(float deltaTime)
{
	this->spaceLevel->updateLevel(deltaTime);

	if (this->spaceLevel->crystalsInstances == this->spaceLevel->playerStats->getPoints())
	{
		std::cout << "You won!" << std::endl;
		this->gameReference->m_stateMachine.addNewState(StateReference(new GameOverState(this->gameReference, "You won!")));
	}

	if (this->spaceLevel->playerStats->getHitPoints() == 0)
	{
		std::cout << "You loose!" << std::endl;
		this->gameReference->m_stateMachine.addNewState(StateReference(new GameOverState(this->gameReference, "You loose!")));
	}
}

void GameState::render(float deltaTime, bool wireframe)
{
	this->spaceLevel->drawLevel(deltaTime, wireframe);
}