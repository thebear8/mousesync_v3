#pragma once
#include <Windows.h>

class mouseHook
{
private:
	HHOOK hook;
	LPARAM (__stdcall *callBack)(int nCode, WPARAM wp, MSLLHOOKSTRUCT* info);

public:
	mouseHook(LPARAM(__stdcall* callBack)(int nCode, WPARAM wp, MSLLHOOKSTRUCT* info))
	{
		this->hook = 0;
		this->callBack = callBack;
	}

	bool hook()
	{
		this->hook = SetWindowsHookExW(WH_MOUSE_LL, (HOOKPROC)callBack, 0, 0);
	}

	bool unHook()
	{
		UnhookWindowsHookEx(hook);
		this->hook = 0;
	}
};

