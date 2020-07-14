#pragma once
#include <Windows.h>

enum class keyboardEventType
{
	keyDown,
	keyUp,
	sysKeyDown,
	sysKeyUp
};

class keyboardEvent
{
	DWORD vkCode;
	keyboardEventType type;
};

