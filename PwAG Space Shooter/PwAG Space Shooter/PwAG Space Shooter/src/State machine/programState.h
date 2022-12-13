#pragma once
#include "pch.h"
#include "../Event system/keyboard.h"
#include "../Event system/mouse.h"

class ProgramState
{
public:
	virtual void processInput(float deltaTime, Keyboard& keyboard, Mouse& mouse) = 0;
	virtual void render(float deltaTime, bool wireframe) = 0;
	virtual void update(float deltaTime) = 0;
	virtual void initialization() = 0;
};