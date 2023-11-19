#pragma once
#include "programState.h"
#include "stateMachine.h"
#include "menuState.h"
#include "gameState.h"

class MenuState : public ProgramState
{
public:
	// Constructors / Destructor
	MenuState(GameReference gameReference);
	~MenuState();

	// Overrides
	void initialization() override;
	void processInput(float deltaTime, Keyboard& keyboard, Mouse& mouse) override;
	void update(float deltaTime) override;
	void render(float deltaTime, bool wireframe) override;

private:
	// References
	GameReference _gameReference;
	Player _camera;

	// Buttons
	Button _newGameButton;
	Button _exitGameButton;

	// Sprites
	Sprite _starsBackground;
	Sprite _logo;
	Sprite _devLogo;
};
