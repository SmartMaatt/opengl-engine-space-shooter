#pragma once
#include "programState.h"
#include "stateMachine.h"
#include "gameAssets.h"
#include "gameOverState.h"

class GameState : public ProgramState
{
public:
	// Constructors / Destructor
	GameState(GameReference gameReference, int currentLevel);
	~GameState();

	// Overrides
	void initialization() override;
	void processInput(float deltaTime, Keyboard& keyboard, Mouse& mouse) override;
	void update(float deltaTime) override;
	void render(float deltaTime, bool wireframe) override;

	// Outcomes
	void winLevel();
	void looseLevel();

private:
	// References
	SpaceLevel* _spaceLevel;
	GameReference _gameReference;

	// Parameters
	int _currentLevel = 0;
	int _lastMousePosX;
	int _lastMousePosY;
	bool _cursorDisabled;
};