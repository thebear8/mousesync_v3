#pragma once
#include <Windows.h>

struct keyboardEvent : KEYBDINPUT
{
	/*DWORD vkCode;
	DWORD scanCode;

	bool keyUp;
	bool extended;

	bool isValid;*/

	keyboardEvent()
	{
		this->wVk = 0;
		this->wScan = 0;
		this->dwFlags = 0;
		this->time = 0;
		this->dwExtraInfo = 0;
	}

	keyboardEvent(DWORD type, KBDLLHOOKSTRUCT* info)
	{
		this->wVk = info->vkCode;
		this->wScan = info->scanCode;
		this->dwFlags |= (!!(info->flags & LLKHF_EXTENDED)) * KEYEVENTF_EXTENDEDKEY;
		this->time = 0;
		this->dwExtraInfo = 0;

		switch (type)
		{
		case WM_KEYDOWN: this->dwFlags &= ~KEYEVENTF_KEYUP; break;
		case WM_KEYUP: this->dwFlags |= KEYEVENTF_KEYUP; break;
		case WM_SYSKEYDOWN: this->dwFlags &= ~KEYEVENTF_KEYUP; break;
		case WM_SYSKEYUP: this->dwFlags |= KEYEVENTF_KEYUP; break;
		}
	}
};

