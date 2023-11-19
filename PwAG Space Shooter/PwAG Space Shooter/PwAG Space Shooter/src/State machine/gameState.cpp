#include "pch.h"
#include "gameState.h"
#include "../Game Objects/spaceLevel.h"

GameState::GameState(GameReference gameReference)
{
	this->gameReference = gameReference;
}

GameState::~GameState() 
{
	delete this->spaceLevel;
}

void GameState::initialization()
{
	this->spaceLevel = new SpaceLevel(this);
	glfwSetInputMode(this->gameReference->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	this->cursorDisabled = true;
}

void GameState::processInput(float deltaTime, Keyboard& keyboard, Mouse& mouse)
{
	this->spaceLevel->input(deltaTime, gameReference, keyboard, mouse);
}

void GameState::update(float deltaTime)
{
	this->spaceLevel->update(deltaTime);
}

void GameState::render(float deltaTime, bool wireframe)
{
	this->spaceLevel->draw(deltaTime, wireframe);
}


/* --->>> Outcomes <<<--- */
void GameState::winLevel()
{
	std::cout << "You won!" << std::endl;
	this->gameReference->m_stateMachine.addNewState(StateReference(new GameOverState(this->gameReference, "You won!")));
}

void GameState::looseLevel()
{
	std::cout << "You loose!" << std::endl;
	this->gameReference->m_stateMachine.addNewState(StateReference(new GameOverState(this->gameReference, "You loose!")));
}
