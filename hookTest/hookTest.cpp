#include <iostream>
#include <Windows.h>

HHOOK kbHook, mHook;

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

LRESULT CALLBACK mouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION)
	{
		MSLLHOOKSTRUCT* info = (MSLLHOOKSTRUCT*)lParam;

		switch (wParam)
		{
		case WM_LBUTTONDOWN: std::cout << "WM_LBUTTONDOWN" << "\n"; break;
		case WM_LBUTTONUP: std::cout << "WM_LBUTTONUP" << "\n"; break;
		case WM_MOUSEMOVE: std::cout << "WM_MOUSEMOVE X: " << info->pt.x << " Y: " << info->pt.y << "\n"; break;
		case WM_MOUSEWHEEL: std::cout << "WM_MOUSEWHEEL" << "\n"; break;
		case WM_MOUSEHWHEEL: std::cout << "WM_MOUSEHWHEEL" << "\n"; break;
		case WM_RBUTTONDOWN: std::cout << "WM_RBUTTONDOWN" << "\n"; break;
		case WM_RBUTTONUP: std::cout << "WM_RBUTTONUP" << "\n"; break;
		case WM_XBUTTONDOWN: std::cout << "WM_XBUTTONDOWN" << "\n"; break;
		case WM_XBUTTONUP: std::cout << "WM_XBUTTONUP" << "\n"; break;
		//default: std::cout << "UNKNOWN" << "\n"; break;
		}
	}

	return CallNextHookEx(mHook, nCode, wParam, lParam);
}

int main()
{
	kbHook = SetWindowsHookExA(WH_KEYBOARD_LL, keyboardProc, 0, 0);
	mHook = SetWindowsHookExA(WH_MOUSE_LL, mouseProc, 0, 0);

	MSG msg;
	while (GetMessageA(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
}