#include "pch.h"
#include "eventManager.h"

void EventManager::windowSizeCallback(int width, int height)
{
	eventQueue.push(EventType::eWindowResized);
}

void EventManager::windowCloseCallback(bool shouldCloseWindow)
{
	if (shouldCloseWindow)
	{
		eventQueue.push(EventType::eWindowClosed);
	}
}

void EventManager::keyCallback(int key, int scancode, int action, int mods)
{
	
	if (this->keyboard)
	{
		Keyboard::Key _key = Keyboard::convertToKey(key);
		if(_key > Keyboard::Key::eKeyNone && _key < Keyboard::Key::eKeyLast)
		{
			if(action == GLFW_PRESS)
			{
				this->eventQueue.emplace(EventType::eKeyPressed);
				this->keyboard->keyState[static_cast<int>(_key)] = true;
			}
			else if(action == GLFW_RELEASE)
			{
				this->eventQueue.emplace(EventType::eKeyReleased);
				this->keyboard->keyState[static_cast<int>(_key)] = false;
			}
		}
	}
}

void EventManager::mouseButtonCallback(int button, int action, int mods)
{
	if (this->mouse) {
		if (action == GLFW_PRESS) {
			this->eventQueue.emplace(EventType::eMouseButtonPressed);
			switch (button) {
			default:
				break;
			case GLFW_MOUSE_BUTTON_LEFT:
				this->mouse->buttonState[static_cast<int>(Mouse::Button::eLeft)] = true;
				break;
			case GLFW_MOUSE_BUTTON_MIDDLE:
				this->mouse->buttonState[static_cast<int>(Mouse::Button::eMiddle)] = true;
				break;
			case GLFW_MOUSE_BUTTON_RIGHT:
				this->mouse->buttonState[static_cast<int>(Mouse::Button::eRight)] = true;
				break;
			}
		}
		else if (action == GLFW_RELEASE) {
			this->eventQueue.emplace(EventType::eMouseButtonReleased);
			switch (button) {
			default:
				break;
			case GLFW_MOUSE_BUTTON_LEFT:
				this->mouse->buttonState[static_cast<int>(Mouse::Button::eLeft)] = false;
				break;
			case GLFW_MOUSE_BUTTON_MIDDLE:
				this->mouse->buttonState[static_cast<int>(Mouse::Button::eMiddle)] = false;
				break;
			case GLFW_MOUSE_BUTTON_RIGHT:
				this->mouse->buttonState[static_cast<int>(Mouse::Button::eRight)] = false;
				break;
			}
		}
	}
}

void EventManager::cursorPositionCallback(double x, double y)
{
	eventQueue.push(EventType::eMouseCursorMoved);
	if (this->mouse)
	{
		this->mouse->posX = static_cast<uint32_t>(x);
		this->mouse->posY = static_cast<uint32_t>(y);
	}
}

void EventManager::registerKeyboard(Keyboard& keyboard)
{
	this->keyboard = &keyboard;
}

void EventManager::registerMouse(Mouse& mouse)
{
	this->mouse = &mouse;
}
