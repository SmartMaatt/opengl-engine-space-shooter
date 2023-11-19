#pragma once
#include "eventType.h"
#include "keyboard.h"
#include "mouse.h"

class EventManager
{
public:
	// Events
	void checkForEvents();
	bool isEventQueueEmpty();
	void clearEventQueue();
	EventType getLatestEventType();

	// Window
	void windowSizeCallback(int width, int height);
	void windowCloseCallback(bool shouldCloseWindow);

	// Keyboard
	void keyCallback(int key, int scancode, int action, int mods);
	void registerKeyboard(Keyboard& keyboard);

	// Mouse
	void mouseButtonCallback(int button, int action, int mods);
	void cursorPositionCallback(double x, double y);
	void registerMouse(Mouse& mouse);

private:
	std::queue<EventType> _eventQueue;
	Keyboard* _keyboard{};
	Mouse* _mouse{};
};