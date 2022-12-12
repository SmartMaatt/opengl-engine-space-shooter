#pragma once
#include "programState.h"
#include "../Game Objects/maze.h"
#include "stateMachine.h"
#include "gameAssets.h"
#include "gameOverState.h"

class GameState : public ProgramState
{
private:
	Maze* maze;
	GameReference gameReference;

	int lastMousePosX;
	int lastMousePosY;

	bool cursorDisabled;

public:
	GameState(GameReference gameReference);
	~GameState();

	void initialization() override;
	void processInput(float deltaTime, Keyboard& keyboard, Mouse& mouse) override;
	void update(float deltaTime) override;
	void render(float deltaTime, bool wireframe) override;
};

