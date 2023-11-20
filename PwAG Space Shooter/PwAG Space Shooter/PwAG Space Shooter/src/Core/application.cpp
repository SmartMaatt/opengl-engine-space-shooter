#include "pch.h"
#include "application.h"
#include "../State machine/gameState.h"
#include "../State machine/menuState.h"
#include "../SourceDep/stb_image.h"

/* --->>> Constructors / Destructor <<<--- */
Application::Application() :
	_tmpDefaultFont(std::move(Font("res/Fonts/Segan.ttf", 18))),
	_fpsLabel(10, 880, "FPS:", _tmpDefaultFont), _fpsValueText(75, 880, "0", _tmpDefaultFont),
	_inputTimeLabel(10, 860, "Input:", _tmpDefaultFont), _inputValueText(75, 860, "0", _tmpDefaultFont),
	_updateTimeLabel(10, 840, "Update:", _tmpDefaultFont), _updateValueText(75, 840, "0", _tmpDefaultFont),
	_renderTimeLabel(10, 820, "Render:", _tmpDefaultFont), _renderValueText(75, 820, "0", _tmpDefaultFont)
{
	glfwInit();

	_initializeText();

	_eventManager.registerKeyboard(_keyboard);
	_eventManager.registerMouse(_mouse);

	_window.attachEventManager(_eventManager);

	_fpsCapCooldown = 1.0 / _fpsCap;
	_fpsCapCooldownLeft = 0.0f;
}

Application::~Application()
{
	glfwTerminate();
}

void Application::run()
{
	// Timers initialization
	_timer.startTimer("deltaTime");
	_timer.startTimer("fps");
	_timer.startTimer("previousMeasure");

	// Reference to state machine and window object
	_gameReference->_stateMachine.addNewState(StateReference(new MenuState(_gameReference)));
	_gameReference->window = _window.getGLFWWindow();

	// Program loop
	while (_mainLoopCondition)
	{
		_gameReference->_stateMachine.changingState();
		_calculateDeltaTime();

		if (_timer.getCurrentDurationInSeconds("previousMeasure") >= _fpsMeasureCooldown)
		{
			_updateFPSThisFrame = true;
		}

		processInput();
		update();
		render();

		if (_updateFPSThisFrame)
		{
			_updateText();
		}
	}
}


/* --->>> Main loop <<<--- */
void Application::processInput()
{
	_timer.startTimer("input");

	_eventManager.checkForEvents();
	while (!_eventManager.isEventQueueEmpty())
	{
		switch (_eventManager.getLatestEventType())
		{
		case EventType::eWindowClosed:
			_mainLoopCondition = false;
			break;

		case EventType::eKeyPressed:
			if (_keyboard.keyState[static_cast<int>(Keyboard::Key::eKeyQ)])
			{
				_wireframeMode = true;
			}

			if (_keyboard.keyState[static_cast<int>(Keyboard::Key::eKeyE)])
			{
				_wireframeMode = false;
			}

			if (_keyboard.keyState[static_cast<int>(Keyboard::Key::eKeyEscape)])
			{
				_mainLoopCondition = false;
			}
			break;
		}
	}

	if (_loopedRender)
	{
		_gameReference->_stateMachine.getCurrentState()->processInput(_deltaTime, _keyboard, _mouse);
	}

	_timer.stopTimer("input");
	_loopedInput = true;
}

void Application::update()
{
	_timer.startTimer("update");

	if (_loopedUpdate)
	{
		_gameReference->_stateMachine.getCurrentState()->update(_deltaTime);
	}

	_timer.stopTimer("update");
	_loopedUpdate = true;
}

void Application::render()
{
	_fpsCapCooldownLeft -= _deltaTime;
	if (_fpsCapCooldownLeft <= 0.0f)
	{
		_frameDuration = _timer.getCurrentDurationInSeconds("fps");
		_timer.startTimer("fps");
		_fpsCapCooldownLeft = _fpsCapCooldown;
		_timer.startTimer("render");

		_window.clearToColor(0, 0, 0);

		// Wireframe mode on
		if (_wireframeMode)
		{
			_wireframeModeOn();
		}
		else
		{
			_wireframeModeOff();
		}

		if (_loopedRender)
		{
			_gameReference->_stateMachine.getCurrentState()->render(_renderDeltaTime, _wireframeMode);
		}
		_drawText();
	}
}


/* --->>> Text <<<--- */
void Application::_initializeText()
{
	ResourceManager::getInstance().loadFont("default", "res/Fonts/Segan.ttf", 42);
	ResourceManager::getInstance().addShaderProgram("text", "shaders/text.vert", "shaders/text.frag");

	// FreeType plugin font shaders
	Shader textVert = Shader::createShaderFromFile("shaders/text.vert", Shader::Type::eVertex);
	Shader textFrag = Shader::createShaderFromFile("shaders/text.frag", Shader::Type::eFragment);

	_textShader.attachShader(textVert);
	_textShader.attachShader(textFrag);
	_textShader.linkShaderProgram();
}

void Application::_updateText()
{
#ifndef DIST
	int32_t fps = static_cast<int32_t>(1.0 / _frameDuration);
	_fpsValueText.setText(std::move(std::to_string(fps)));

	double inputDuration = _timer.getMeasuredDurationInMiliseconds("input");
	std::stringstream streamForInput;
	streamForInput << std::fixed << std::setprecision(4);
	streamForInput << inputDuration;
	_inputValueText.setText(streamForInput.str() + "ms");

	double updateDuration = _timer.getMeasuredDurationInMiliseconds("update");
	std::stringstream streamForUpdate;
	streamForUpdate << std::fixed << std::setprecision(4);
	streamForUpdate << updateDuration;
	_updateValueText.setText(streamForUpdate.str() + "ms");

	double renderDuration = _timer.getMeasuredDurationInMiliseconds("render");
	std::stringstream streamForRender;
	streamForRender << std::fixed << std::setprecision(4);
	streamForRender << renderDuration;
	_renderValueText.setText(streamForRender.str() + "ms");

	_updateFPSThisFrame = false;
	_timer.startTimer("previousMeasure");
#endif
}

void Application::_drawText()
{
#ifndef DIST
	_textShader.useShader();
	auto projection = glm::ortho(0.0f, static_cast<float>(Config::g_defaultWidth), 0.0f, static_cast<float>(Config::g_defaultHeight));
	_textShader.setMat4("MVP", projection);

	_fpsLabel.render(_textShader);
	_fpsValueText.render(_textShader);

	_inputTimeLabel.render(_textShader);
	_inputValueText.render(_textShader);
	_updateTimeLabel.render(_textShader);
	_updateValueText.render(_textShader);
	_renderTimeLabel.render(_textShader);
	_renderValueText.render(_textShader);
#endif
	_window.swapBuffers();	// Render buffer swapping
	_timer.stopTimer("render");
	_loopedRender = true;
}


/* --->>> Wirefame mode <<<--- */
void Application::_wireframeModeOn()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Application::_wireframeModeOff()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


/* --->>> Time calculations <<<--- */
void Application::_calculateDeltaTime()
{
	_deltaTime = _timer.getCurrentDurationInSeconds("deltaTime");
	_timer.startTimer("deltaTime");
}

void Application::_calculateRenderDeltaTime()
{
	_renderDeltaTime = _frameDuration;
}