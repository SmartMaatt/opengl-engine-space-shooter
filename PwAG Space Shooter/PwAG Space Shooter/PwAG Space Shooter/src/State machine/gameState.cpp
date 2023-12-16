#include "pch.h"
#include "gameState.h"
#include "../Rendering system/Space level/spaceLevel.h"

/* --->>> Constructors / Destructor <<<--- */
GameState::GameState(GameReference gameReference, int currentLevel)
{
	_currentLevel = currentLevel;
	Debug::Log(std::to_string(_currentLevel));
	_gameReference = gameReference;
}

GameState::~GameState() 
{
	delete _spaceLevel;
}


/* --->>> Overrides <<<--- */
void GameState::initialization()
{
	_spaceLevel = new SpaceLevel(this, _currentLevel);
	glfwSetInputMode(_gameReference->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	_cursorDisabled = true;
}

void GameState::processInput(float deltaTime, Keyboard& keyboard, Mouse& mouse)
{
	_spaceLevel->input(deltaTime, _gameReference, keyboard, mouse);
}

void GameState::update(float deltaTime)
{
	_spaceLevel->update(deltaTime);
}

void GameState::render(float deltaTime, bool wireframe)
{
	_spaceLevel->draw(deltaTime, wireframe);
}


/* --->>> Outcomes <<<--- */
void GameState::winLevel()
{
	Debug::LogSuccess("You won!");
	_gameReference->_stateMachine.addNewState(StateReference(new GameOverState(_gameReference, "You won!", _currentLevel)));
}

void GameState::looseLevel()
{
	Debug::LogError("You loose!");
	_gameReference->_stateMachine.addNewState(StateReference(new GameOverState(_gameReference, "You loose!", _currentLevel)));
}
