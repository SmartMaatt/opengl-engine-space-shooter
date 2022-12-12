#pragma once
#include "eventType.h"
#include "keyboard.h"
#include "mouse.h"

class EventManager
{
public:
#pragma region Inline functions
	void checkForEvents()
	{
		glfwPollEvents();
	}
	bool isEventQueueEmpty()
	{
		return eventQueue.empty();
	}
	void clearEventQueue()
	{
		while (!eventQueue.empty())
		{
			eventQueue.pop();
		}
	}
	EventType getLatestEventType()
	{
		//wait till there is an event to return
		while (eventQueue.empty());

		auto tmp = eventQueue.front();
		eventQueue.pop();
		return tmp;
	}
#pragma endregion

	void windowSizeCallback(int width, int height);
	void windowCloseCallback(bool shouldCloseWindow);

	void keyCallback(int key, int scancode, int action, int mods);

	void mouseButtonCallback(int button, int action, int mods);
	void cursorPositionCallback(double x, double y);

	void registerKeyboard(Keyboard& keyboard);
	void registerMouse(Mouse& mouse);
private:
	std::queue<EventType> eventQueue;
	Keyboard* keyboard{};
	Mouse* mouse{};
};