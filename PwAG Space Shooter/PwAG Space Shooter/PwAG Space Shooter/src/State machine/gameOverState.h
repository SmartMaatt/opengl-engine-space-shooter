#pragma once
#include "programState.h"
#include "stateMachine.h"
#include "gameAssets.h"
#include "menuState.h"

class GameOverState : public ProgramState
{
public:
	// Constructors / Destructor
	GameOverState(GameReference gameReference, std::string header, int currentLevelID);
	~GameOverState();

	// Overrides
	void initialization() override;
	void processInput(float deltaTime, Keyboard& keyboard, Mouse& mouse) override;
	void update(float deltaTime) override;
	void render(float deltaTime, bool wireframe) override;

private:
	//State
	bool isNextLevel = false;
	
	// References
	GameReference _gameReference;

	// Buttons
	Button _winLabel;
	Button _menuButton;
	Button _nextLevel;

	// Sprites
	Sprite _starsBackground;
	Sprite _logo;
	Sprite _devLogo;
};
