#include "pch.h"
#include "menuState.h"
#include "../SourceDep/stb_image.h"

/* --->>> Constructors / Destructor <<<--- */
MenuState::MenuState(GameReference gameReference) :
	_newGameButton("New game", { 900, 400 }, { 0.7, 0.7, 0.0 }),
	_chooseLevelButton("Choose level", { 900, 470 }, { 0.7, 0.7, 0.0 }),
	_exitGameButton("Exit", { 900, 540 }, { 0.7, 0.7, 0.0 }),
	_returnButton("Return", { 900, 610 }, { 0.7, 0.7, 0.0 }),
	_camera(glm::vec3(0, 0, 0)),
	_starsBackground("res/Textures/stars.jpg", 1600, 900, 800, 450, false),
	_logo("res/Textures/logo.png", 400, 400, 650, 450, true),
	_devLogo("res/Textures/devLogo.png", 150, 150, 1600 - 85, 900 - 85, true)
{
	_gameReference = gameReference;
	_newGameButton.setAction([this]()
	{
		_gameReference->_stateMachine.addNewState(StateReference(new GameState(_gameReference, 0)));
	});

	_chooseLevelButton.setAction([this]()
	{
		isChooseLevel = true;
	});

	_exitGameButton.setAction([this]()
	{
		glfwDestroyWindow(_gameReference->window);
		glfwTerminate();
		exit(EXIT_SUCCESS);
	});

	createLevelButtonsVector();
	int counter = 0;
	for (Button* button : _levelButtonsVector)
	{
		button->setAction([this, counter]()
		{
			_gameReference->_stateMachine.addNewState(StateReference(new GameState(_gameReference, counter)));
		});
		counter++;
	}

	_returnButton.setAction([this]()
	{
		isChooseLevel = false;
	});
}

MenuState::~MenuState()
{
	for (Button* button : _levelButtonsVector)
	{
		delete button;
	}
	_levelButtonsVector.clear();
}


/* --->>> Overrides <<<--- */
void MenuState::initialization() {}
void MenuState::processInput(float deltaTime, Keyboard& keyboard, Mouse& mouse)
{
	if (!isChooseLevel)
	{
		_newGameButton.update(mouse);
		_chooseLevelButton.update(mouse);
		_exitGameButton.update(mouse);
	}
	else
	{
		for (Button* button : _levelButtonsVector)
		{
			button->update(mouse);
		}
		_returnButton.update(mouse);
	}
}

void MenuState::update(float deltaTime) {}
void MenuState::render(float deltaTime, bool wireframe)
{
	_starsBackground.draw();
	_logo.draw();
	_devLogo.draw();

	if (!isChooseLevel)
	{
		_newGameButton.draw();
		_chooseLevelButton.draw();
		_exitGameButton.draw();
	}
	else
	{
		for (Button* button : _levelButtonsVector)
		{
			button->draw();
		}
		_returnButton.draw();
	}
}

void MenuState::createLevelButtonsVector()
{
	for (int i = 0; i < 5; i++)
	{
		std::string text = "Level " + std::to_string(i + 1);
		glm::vec2 position = glm::vec2(900, 240 + 70 * i);
		glm::vec3 color = glm::vec3(0.7, 0.7, 0.0);

		Button* newButton = new Button(text, position, color);
		_levelButtonsVector.push_back(newButton);
	}
}
