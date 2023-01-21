#include "pch.h"
#include "gameOverState.h"

GameOverState::GameOverState(GameReference gameReference, std::string header) :
	menuButton("Return", { 850, 470 }, { 0.7, 0.7, 0.0 }),
	winLabel(header, { 850, 400 }, { 0.7, 0.7, 0.0 }),
	stars("res/Textures/stars.jpg", 1600, 900, 800, 450, false),
	logo("res/Textures/logo.png", 400, 400, 650, 450, true),
	devLogo("res/Textures/devLogo.png", 150, 150, 1600 - 85, 900 - 85, true)
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
	stars.Draw();
	logo.Draw();
	devLogo.Draw();

	menuButton.draw();
	winLabel.draw();
}
