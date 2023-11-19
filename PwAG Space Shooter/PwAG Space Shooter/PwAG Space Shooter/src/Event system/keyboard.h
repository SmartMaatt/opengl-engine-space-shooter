#pragma once
#include <cstdint>
#include "GLFW/glfw3.h"

struct Keyboard
{
	enum class Key
	{
		eKeyNone = -1,

		eKeyA,
		eKeyB,
		eKeyC,
		eKeyD,
		eKeyE,
		eKeyF,
		eKeyG,
		eKeyH,
		eKeyI,
		eKeyJ,
		eKeyK,
		eKeyL,
		eKeyM,
		eKeyN,
		eKeyO,
		eKeyQ,
		eKeyP,
		eKeyR,
		eKeyS,
		eKeyT,
		eKeyU,
		eKeyW,
		eKeyV,
		eKeyX,
		eKeyY,
		eKeyZ,

		eKey1,
		eKey2,
		eKey3,
		eKey4,
		eKey5,
		eKey6,
		eKey7,
		eKey8,
		eKey9,
		eKey0,

		eKeyF1,
		eKeyF2,
		eKeyF3,
		eKeyF4,
		eKeyF5,
		eKeyF6,
		eKeyF7,
		eKeyF8,
		eKeyF9,
		eKeyF10,
		eKeyF11,
		eKeyF12,

		eKeyArrowUp,
		eKeyArrowLeft,
		eKeyArrowRight,
		eKeyArrowDown,

		eKeySpace,

		eKeyComma,
		eKeyDot,
		eKeySlash,
		eKeySemicolon,
		eKeyApostrophe,
		eKeyBackslash,
		eLeftBracket,
		eRightBracket,
		eKeyGraveAccent,
		eKeyMinus,
		eKeyEqual,
		eKeyBackspace,
		eKeyEscape,
		eKeyLeftShift,

		eKeyLast
	};

	static Key convertToKey(int glfwKey)
	{
		switch (glfwKey)
		{
		default:
			return Key::eKeyNone;
		case GLFW_KEY_A:
			return Key::eKeyA;
		case GLFW_KEY_B:
			return Key::eKeyB;
		case GLFW_KEY_C:
			return Key::eKeyC;
		case GLFW_KEY_D:
			return Key::eKeyD;
		case GLFW_KEY_E:
			return Key::eKeyE;
		case GLFW_KEY_F:
			return Key::eKeyF;
		case GLFW_KEY_G:
			return Key::eKeyG;
		case GLFW_KEY_H:
			return Key::eKeyH;
		case GLFW_KEY_I:
			return Key::eKeyI;
		case GLFW_KEY_J:
			return Key::eKeyJ;
		case GLFW_KEY_K:
			return Key::eKeyK;
		case GLFW_KEY_L:
			return Key::eKeyL;
		case GLFW_KEY_M:
			return Key::eKeyM;
		case GLFW_KEY_N:
			return Key::eKeyN;
		case GLFW_KEY_O:
			return Key::eKeyO;
		case GLFW_KEY_Q:
			return Key::eKeyQ;
		case GLFW_KEY_P:
			return Key::eKeyP;
		case GLFW_KEY_R:
			return Key::eKeyR;
		case GLFW_KEY_S:
			return Key::eKeyS;
		case GLFW_KEY_T:
			return Key::eKeyT;
		case GLFW_KEY_U:
			return Key::eKeyU;
		case GLFW_KEY_W:
			return Key::eKeyW;
		case GLFW_KEY_V:
			return Key::eKeyV;
		case GLFW_KEY_X:
			return Key::eKeyX;
		case GLFW_KEY_Y:
			return Key::eKeyY;
		case GLFW_KEY_Z:
			return Key::eKeyZ;
		case GLFW_KEY_1:
			return Key::eKey1;
		case GLFW_KEY_2:
			return Key::eKey2;
		case GLFW_KEY_3:
			return Key::eKey3;
		case GLFW_KEY_4:
			return Key::eKey4;
		case GLFW_KEY_5:
			return Key::eKey5;
		case GLFW_KEY_6:
			return Key::eKey6;
		case GLFW_KEY_7:
			return Key::eKey7;
		case GLFW_KEY_8:
			return Key::eKey8;
		case GLFW_KEY_9:
			return Key::eKey9;
		case GLFW_KEY_0:
			return Key::eKey0;
		case GLFW_KEY_F1:
			return Key::eKeyF1;
		case GLFW_KEY_F2:
			return Key::eKeyF2;
		case GLFW_KEY_F3:
			return Key::eKeyF3;
		case GLFW_KEY_F4:
			return Key::eKeyF4;
		case GLFW_KEY_F5:
			return Key::eKeyF5;
		case GLFW_KEY_F6:
			return Key::eKeyF6;
		case GLFW_KEY_F7:
			return Key::eKeyF7;
		case GLFW_KEY_F8:
			return Key::eKeyF8;
		case GLFW_KEY_F9:
			return Key::eKeyF9;
		case GLFW_KEY_F10:
			return Key::eKeyF10;
		case GLFW_KEY_F11:
			return Key::eKeyF11;
		case GLFW_KEY_F12:
			return Key::eKeyF12;
		case GLFW_KEY_UP:
			return Key::eKeyArrowUp;
		case GLFW_KEY_LEFT:
			return Key::eKeyArrowLeft;
		case GLFW_KEY_RIGHT:
			return Key::eKeyArrowRight;
		case GLFW_KEY_DOWN:
			return Key::eKeyArrowDown;
		case GLFW_KEY_SPACE:
			return Key::eKeySpace;
		case GLFW_KEY_COMMA:
			return Key::eKeyComma;
		case GLFW_KEY_PERIOD:
			return Key::eKeyDot;
		case GLFW_KEY_SLASH:
			return Key::eKeySlash;
		case GLFW_KEY_SEMICOLON:
			return Key::eKeySemicolon;
		case GLFW_KEY_APOSTROPHE:
			return Key::eKeyApostrophe;
		case GLFW_KEY_BACKSLASH:
			return Key::eKeyBackslash;
		case GLFW_KEY_LEFT_BRACKET:
			return Key::eLeftBracket;
		case GLFW_KEY_RIGHT_BRACKET:
			return Key::eRightBracket;
		case GLFW_KEY_GRAVE_ACCENT:
			return Key::eKeyGraveAccent;
		case GLFW_KEY_MINUS:
			return Key::eKeyMinus;
		case GLFW_KEY_EQUAL:
			return Key::eKeyEqual;
		case GLFW_KEY_BACKSPACE:
			return Key::eKeyBackspace;
		case GLFW_KEY_ESCAPE:
			return Key::eKeyEscape;
		case GLFW_KEY_LEFT_SHIFT:
			return Key::eKeyLeftShift;
		}
	}

	bool keyState[static_cast<uint32_t>(Key::eKeyLast)]{};
};