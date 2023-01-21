#pragma once
#include "programState.h"
#include "stateMachine.h"
#include "menuState.h"
#include "gameState.h"

class MenuState : public ProgramState
{
private:
	GameReference gameReference;
	Player camera;

	Button newGameButton;
	Button exitGameButton;

	Sprite stars;
	Sprite logo;
	Sprite devLogo;

public:
	MenuState(GameReference gameReference);
	~MenuState();

	void initialization() override;
	void processInput(float deltaTime, Keyboard& keyboard, Mouse& mouse) override;
	void update(float deltaTime) override;
	void render(float deltaTime, bool wireframe) override;
};
