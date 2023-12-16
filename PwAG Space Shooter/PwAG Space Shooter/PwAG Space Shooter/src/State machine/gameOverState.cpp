#include "pch.h"
#include "gameOverState.h"

/* --->>> Constructors / Destructor <<<--- */
GameOverState::GameOverState(GameReference gameReference, std::string header, int currentLevelID) :
	_winLabel(header, { 900, 400 }, { 0.7, 0.7, 0.0 }),
	_menuButton("Return", { 900, 470 }, { 0.7, 0.7, 0.0 }),
	_nextLevel("Next level", { 900, 540 }, { 0.7, 0.7, 0.0 }),
	_starsBackground("res/Textures/stars.jpg", 1600, 900, 800, 450, false),
	_logo("res/Textures/logo.png", 400, 400, 650, 450, true),
	_devLogo("res/Textures/devLogo.png", 150, 150, 1600 - 85, 900 - 85, true)
{
	_gameReference = gameReference;
	glfwSetInputMode(_gameReference->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	_menuButton.setAction([this]()
	{
		_gameReference->_stateMachine.addNewState(StateReference(new MenuState(_gameReference)));
	});

	currentLevelID++;
	int newLevelID = currentLevelID;
	if (newLevelID < 5)
	{
		isNextLevel = true;
		_nextLevel.setAction([this,newLevelID]()
		{
			_gameReference->_stateMachine.addNewState(StateReference(new GameState(_gameReference, newLevelID)));
		});
	}
	else
	{
		isNextLevel = false;
	}
}

GameOverState::~GameOverState() {}


/* --->>> Overrides <<<--- */
void GameOverState::initialization() {}
void GameOverState::processInput(float deltaTime, Keyboard& keyboard, Mouse& mouse)
{
	_menuButton.update(mouse);

	if (isNextLevel)
	{
		_nextLevel.update(mouse);
	}
}

void GameOverState::update(float deltaTime) {}
void GameOverState::render(float deltaTime, bool wireframe)
{
	_starsBackground.draw();
	_logo.draw();
	_devLogo.draw();

	_menuButton.draw();
	_winLabel.draw();
	if (isNextLevel)
	{
		_nextLevel.draw();
	}
}
