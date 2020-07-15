#pragma once
#include <Windows.h>

enum class keyboardEventType
{
	keyDown,
	keyUp,
	sysKeyDown,
	sysKeyUp,
	unknown
};

struct keyboardEvent
{
	DWORD vkCode;
	keyboardEventType type;

	keyboardEvent()
	{
		this->vkCode = 0;
		this->type = keyboardEventType::unknown;
	}

	keyboardEvent(DWORD vkCode, DWORD type)
	{
		this->vkCode = vkCode;

		switch (type)
		{
		case WM_KEYDOWN: this->type = keyboardEventType::keyDown; break;
		case WM_KEYUP: this->type = keyboardEventType::keyUp; break;
		case WM_SYSKEYDOWN: this->type = keyboardEventType::sysKeyDown; break;
		case WM_SYSKEYUP: this->type = keyboardEventType::sysKeyUp; break;
		default: this->type = keyboardEventType::unknown;
		}
	}
};

