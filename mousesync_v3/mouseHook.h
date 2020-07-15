#pragma once
#include <Windows.h>

class mouseHook
{
private:
	HHOOK hhook;
	LPARAM (__stdcall *callBack)(int nCode, WPARAM wp, MSLLHOOKSTRUCT* info);

public:
	mouseHook(LPARAM(__stdcall* callBack)(int nCode, WPARAM wp, MSLLHOOKSTRUCT* info))
	{
		this->hhook = 0;
		this->callBack = callBack;
	}

	bool hook()
	{
		this->hhook = SetWindowsHookExW(WH_MOUSE_LL, (HOOKPROC)callBack, 0, 0);
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

