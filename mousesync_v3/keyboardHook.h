#pragma once
#include <Windows.h>

class keyboardHook
{
private:
	HHOOK hook;
	LPARAM(__stdcall* callBack)(int nCode, WPARAM wp, KBDLLHOOKSTRUCT* info);

public:
	keyboardHook(LPARAM(__stdcall* callBack)(int nCode, WPARAM wp, KBDLLHOOKSTRUCT* info))
	{
		this->hook = 0;
		this->callBack = callBack;
	}

	bool hook()
	{
		this->hook = SetWindowsHookExW(WH_KEYBOARD_LL, (HOOKPROC)callBack, 0, 0);
	}

	bool unHook()
	{
		UnhookWindowsHookEx(hook);
		this->hook = 0;
	}

	HHOOK getHook()
	{
		return hook;
	}
};

