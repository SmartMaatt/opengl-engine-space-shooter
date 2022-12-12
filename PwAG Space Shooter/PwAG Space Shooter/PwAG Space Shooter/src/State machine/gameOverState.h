#pragma once
#include "programState.h"
#include "stateMachine.h"
#include "gameAssets.h"
#include "menuState.h"

class GameOverState : public ProgramState
{
private:
	GameReference gameReference;

	Button winLabel;
	Button menuButton;

public:
	GameOverState(GameReference gameReference);
	~GameOverState();

	void initialization() override;
	void processInput(float deltaTime, Keyboard& keyboard, Mouse& mouse) override;
	void update(float deltaTime) override;
	void render(float deltaTime, bool wireframe) override;
};
