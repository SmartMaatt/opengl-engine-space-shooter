#pragma once
#include "../Window/window.h"
#include "../Rendering system/Text/text.h"
#include "../State machine/stateMachine.h"
#include "../State machine/gameAssets.h"

#pragma region GLFW event callbacks
void framebuffer_size_callback(GLFWwindow* window, const int width, const int height);
void window_close_callback(GLFWwindow* window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
#pragma endregion

class Application
{
	friend void framebuffer_size_callback(GLFWwindow* window, const int width, const int height);
	friend void window_close_callback(GLFWwindow* window);
	friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

public:
	// Constructors / Destructor
	Application();
	~Application();
	void run();

	// Main loop
	void processInput();
	void update();
	void render();

private:
	// Text
	void _initializeText();
	void _updateText();
	void _drawText();

	// Wireframe mode
	void _wireframeModeOn();
	void _wireframeModeOff();

	// Time calculations
	void _calculateDeltaTime();
	void _calculateRenderDeltaTime();

	// References
	Window _window;
	EventManager _eventManager;
	Keyboard _keyboard;
	Mouse _mouse;

	// Text rendering
	Font _tmpDefaultFont;
	ShaderProgram _textShader;

	// State machine
	GameReference _gameReference = std::make_shared<GameAssets>();

	// Time related
	double _deltaTime = 0.0f;
	double _renderDeltaTime = 0.0f;

	uint32_t _fpsCap = 240;
	double _fpsCapCooldown;					// In seconds
	double _fpsCapCooldownLeft;
	double _frameDuration = 0.0f;
	Timer _timer;

	double _fpsMeasureCooldown = 0.5;		// In seconds
	double _fpsMeasureCooldownLeft = 0.0f;
	bool _updateFPSThisFrame = false;

	// Info labels
	Text _fpsLabel;
	Text _fpsValueText;

	Text _inputTimeLabel;
	Text _inputValueText;

	Text _updateTimeLabel;
	Text _updateValueText;

	Text _renderTimeLabel;
	Text _renderValueText;

	// States
	bool _mainLoopCondition = true;
	bool _wireframeMode = false;
	bool _loopedInput = false;
	bool _loopedRender = false;
	bool _loopedUpdate = false;
};