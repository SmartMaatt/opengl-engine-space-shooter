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
	//State
	bool isChooseLevel = false;

	// References
	GameReference _gameReference;
	Player _camera;

	// Buttons
	Button _newGameButton;
	Button _chooseLevelButton;
	Button _returnButton;
	Button _exitGameButton;
	std::vector<Button*> _levelButtonsVector = std::vector<Button*>();
	void createLevelButtonsVector();

	// Sprites
	Sprite _starsBackground;
	Sprite _logo;
	Sprite _devLogo;
};
