#pragma once
#include <Windows.h>

class keyboardHook
{
private:
	HHOOK hhook;
	LPARAM(__stdcall* callBack)(int nCode, WPARAM wp, KBDLLHOOKSTRUCT* info);

public:
	keyboardHook(LPARAM(__stdcall* callBack)(int nCode, WPARAM wp, KBDLLHOOKSTRUCT* info))
	{
		this->hhook = 0;
		this->callBack = callBack;
	}

	bool hook()
	{
		this->hhook = SetWindowsHookExW(WH_KEYBOARD_LL, (HOOKPROC)callBack, 0, 0);
	}

	bool unHook()
	{
		UnhookWindowsHookEx(hhook);
		this->hhook = 0;
	}

	HHOOK getHook()
	{
		return hhook;
	}
};

