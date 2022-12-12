#pragma once
#include <cstdint>

struct Mouse
{
	enum class Button
	{
		eNone = -1,
		eLeft = 0,
		eMiddle,
		eRight,
		eLast			// Number of buttons available
	};

	bool buttonState[static_cast<uint32_t>(Button::eLast)]{};
	uint32_t posX{};
	uint32_t posY{};
};
