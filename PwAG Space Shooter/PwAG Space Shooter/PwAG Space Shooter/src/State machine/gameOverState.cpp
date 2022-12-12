#include "pch.h"
#include "gameOverState.h"

GameOverState::GameOverState(GameReference gameReference)
	: menuButton("Return", { 700, 175 }, { 0.7, 0.7, 0.0 }),
	winLabel("Victory!", { 700, 100 }, { 0.0, 0.7, 0.0 })
{
	this->gameReference = gameReference;

	glfwSetInputMode(this->gameReference->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	menuButton.setAction([this]()
		{
			this->gameReference->m_stateMachine.addNewState(StateReference(new MenuState(this->gameReference)));
		});
}

GameOverState::~GameOverState()
{
}

void GameOverState::initialization()
{

}

void GameOverState::processInput(float deltaTime, Keyboard& keyboard, Mouse& mouse)
{
	menuButton.update(mouse);
}

void GameOverState::update(float deltaTime)
{

}

void GameOverState::render(float deltaTime, bool wireframe)
{
	menuButton.draw();
	winLabel.draw();
}
