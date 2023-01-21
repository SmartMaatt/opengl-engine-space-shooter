#include "pch.h"
#include "menuState.h"
#include "../SourceDep/stb_image.h"

MenuState::MenuState(GameReference gameReference) :
	newGameButton("New game", { 850, 400 }, { 0.7, 0.7, 0.0 }),
	exitGameButton("Exit", { 850, 470 }, { 0.7, 0.7, 0.0 }),
	camera(glm::vec3(0, 0, 0)),
	stars("res/Textures/stars.jpg", 1600, 900, 800, 450, false),
	logo("res/Textures/logo.png", 400, 400, 650, 450, true),
	devLogo("res/Textures/devLogo.png", 150, 150, 1600-85, 900-85, true)
{
	this->gameReference = gameReference;

	newGameButton.setAction([this]()
		{
			this->gameReference->m_stateMachine.addNewState(StateReference(new GameState(this->gameReference)));
		});

	exitGameButton.setAction([this]()
		{
			glfwDestroyWindow(this->gameReference->window);

			glfwTerminate();
			exit(EXIT_SUCCESS);
		});
}

MenuState::~MenuState()
{

}

void MenuState::initialization()
{

}

void MenuState::processInput(float deltaTime, Keyboard& keyboard, Mouse& mouse)
{
	newGameButton.update(mouse);
	exitGameButton.update(mouse);
}

void MenuState::update(float deltaTime)
{

}

void MenuState::render(float deltaTime, bool wireframe)
{
	stars.Draw();
	logo.Draw();
	devLogo.Draw();

	newGameButton.draw();
	exitGameButton.draw();
}
