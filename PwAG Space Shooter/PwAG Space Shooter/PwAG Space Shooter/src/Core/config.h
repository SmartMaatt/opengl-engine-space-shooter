#pragma once
#include "../Window/windowMode.h"

namespace Config
{
	constexpr WindowMode g_defaultWindowMode = WindowMode::eWindowed;

	constexpr uint32_t g_defaultWidth = 1600;
	constexpr uint32_t g_defaultHeight = 900;

	constexpr const char* g_defaultWindowTitle = "Hunters of empire";
}