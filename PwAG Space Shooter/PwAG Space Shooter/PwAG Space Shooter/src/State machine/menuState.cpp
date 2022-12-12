#include "pch.h"
#include "menuState.h"

MenuState::MenuState(GameReference gameReference)
	: newGameButton("New game", { 700, 100 }, { 0.7, 0.7, 0.0 }),
	exitGameButton("Exit", { 745, 175 }, { 0.7, 0.7, 0.0 }), camera(glm::vec3(0, 0, 0))
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
	newGameButton.draw();
	exitGameButton.draw();
}
