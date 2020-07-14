#include <iostream>
#include <Windows.h>

HHOOK kbHook;

LRESULT CALLBACK keyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION)
	{
		if (wParam == WM_KEYDOWN)
		{
			std::cout << "WM_KEYDOWN: \n";
		}
		if (wParam == WM_KEYUP)
		{
			std::cout << "WM_KEYUP: \n";
		}
		if (wParam == WM_SYSKEYDOWN)
		{
			std::cout << "WM_SYSKEYDOWN: \n";
		}
		if (wParam == WM_SYSKEYUP)
		{
			std::cout << "WM_SYSKEYUP: \n";
		}
	}

	return CallNextHookEx(kbHook, nCode, wParam, lParam);
}

int main()
{
	SetWindowsHookExA(WH_KEYBOARD_LL, keyboardProc, 0, 0);

	MSG msg;
	while (GetMessageA(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
}