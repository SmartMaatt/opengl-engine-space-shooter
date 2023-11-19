#include "pch.h"
#include "eventManager.h"

/* --->>> Events <<<--- */
void EventManager::checkForEvents()
{
	glfwPollEvents();
}

bool EventManager::isEventQueueEmpty()
{
	return _eventQueue.empty();
}

void EventManager::clearEventQueue()
{
	while (!_eventQueue.empty())
	{
		_eventQueue.pop();
	}
}

EventType EventManager::getLatestEventType()
{
	// Wait till there is an event to return
	while (_eventQueue.empty());

	auto tmp = _eventQueue.front();
	_eventQueue.pop();
	return tmp;
}


/* --->>> Window <<<--- */
void EventManager::windowSizeCallback(int width, int height)
{
	_eventQueue.push(EventType::eWindowResized);
}

void EventManager::windowCloseCallback(bool shouldCloseWindow)
{
	if (shouldCloseWindow)
	{
		_eventQueue.push(EventType::eWindowClosed);
	}
}


/* --->>> Keyboard <<<--- */
void EventManager::keyCallback(int key, int scancode, int action, int mods)
{
	if (_keyboard)
	{
		Keyboard::Key _key = Keyboard::convertToKey(key);
		if (_key > Keyboard::Key::eKeyNone && _key < Keyboard::Key::eKeyLast)
		{
			if (action == GLFW_PRESS)
			{
				_eventQueue.emplace(EventType::eKeyPressed);
				_keyboard->keyState[static_cast<int>(_key)] = true;
			}
			else if (action == GLFW_RELEASE)
			{
				_eventQueue.emplace(EventType::eKeyReleased);
				_keyboard->keyState[static_cast<int>(_key)] = false;
			}
		}
	}
}

void EventManager::registerKeyboard(Keyboard& keyboard)
{
	_keyboard = &keyboard;
}


/* --->>> Mouse <<<--- */
void EventManager::mouseButtonCallback(int button, int action, int mods)
{
	if (_mouse)
	{
		if (action == GLFW_PRESS)
		{
			_eventQueue.emplace(EventType::eMouseButtonPressed);
			switch (button) {
			default:
				break;
			case GLFW_MOUSE_BUTTON_LEFT:
				_mouse->buttonState[static_cast<int>(Mouse::Button::eLeft)] = true;
				break;
			case GLFW_MOUSE_BUTTON_MIDDLE:
				_mouse->buttonState[static_cast<int>(Mouse::Button::eMiddle)] = true;
				break;
			case GLFW_MOUSE_BUTTON_RIGHT:
				_mouse->buttonState[static_cast<int>(Mouse::Button::eRight)] = true;
				break;
			}
		}
		else if (action == GLFW_RELEASE)
		{
			_eventQueue.emplace(EventType::eMouseButtonReleased);
			switch (button)
			{
			default:
				break;
			case GLFW_MOUSE_BUTTON_LEFT:
				_mouse->buttonState[static_cast<int>(Mouse::Button::eLeft)] = false;
				break;
			case GLFW_MOUSE_BUTTON_MIDDLE:
				_mouse->buttonState[static_cast<int>(Mouse::Button::eMiddle)] = false;
				break;
			case GLFW_MOUSE_BUTTON_RIGHT:
				_mouse->buttonState[static_cast<int>(Mouse::Button::eRight)] = false;
				break;
			}
		}
	}
}

void EventManager::cursorPositionCallback(double x, double y)
{
	_eventQueue.push(EventType::eMouseCursorMoved);
	if (_mouse)
	{
		_mouse->posX = static_cast<uint32_t>(x);
		_mouse->posY = static_cast<uint32_t>(y);
	}
}

void EventManager::registerMouse(Mouse& mouse)
{
	_mouse = &mouse;
}
