#include "pch.h"
#include "menuState.h"
#include "../SourceDep/stb_image.h"

/* --->>> Constructors / Destructor <<<--- */
MenuState::MenuState(GameReference gameReference) :
	_newGameButton("New game", { 850, 400 }, { 0.7, 0.7, 0.0 }),
	_exitGameButton("Exit", { 850, 470 }, { 0.7, 0.7, 0.0 }),
	_camera(glm::vec3(0, 0, 0)),
	_starsBackground("res/Textures/stars.jpg", 1600, 900, 800, 450, false),
	_logo("res/Textures/logo.png", 400, 400, 650, 450, true),
	_devLogo("res/Textures/devLogo.png", 150, 150, 1600 - 85, 900 - 85, true)
{
	_gameReference = gameReference;
	_newGameButton.setAction([this]()
	{
		_gameReference->_stateMachine.addNewState(StateReference(new GameState(_gameReference)));
	});

	_exitGameButton.setAction([this]()
	{
		glfwDestroyWindow(_gameReference->window);
		glfwTerminate();
		exit(EXIT_SUCCESS);
	});
}

MenuState::~MenuState() {}


/* --->>> Overrides <<<--- */
void MenuState::initialization() {}
void MenuState::processInput(float deltaTime, Keyboard& keyboard, Mouse& mouse)
{
	_newGameButton.update(mouse);
	_exitGameButton.update(mouse);
}

void MenuState::update(float deltaTime) {}
void MenuState::render(float deltaTime, bool wireframe)
{
	_starsBackground.draw();
	_logo.draw();
	_devLogo.draw();

	_newGameButton.draw();
	_exitGameButton.draw();
}
