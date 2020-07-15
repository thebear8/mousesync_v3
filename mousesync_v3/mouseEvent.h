#pragma once
#include <Windows.h>

struct mouseEvent : MOUSEINPUT
{
	mouseEvent()
	{
		this->dx = 0;
		this->dy = 0;
		this->dwFlags = 0;
		this->mouseData = 0;
	}

	mouseEvent(DWORD type, MSLLHOOKSTRUCT* info)
	{
		this->dx = ((float)info->pt.x) / ((float)GetSystemMetrics(SM_CXSCREEN)) * 65536.f;
		this->dy = ((float)info->pt.y) / ((float)GetSystemMetrics(SM_CYSCREEN)) * 65536.f;
		this->dwFlags = 0;
		this->mouseData = 0;

		switch (type)
		{
		case WM_LBUTTONDOWN:
			this->dwFlags = MOUSEEVENTF_LEFTDOWN;
			break;
		case WM_LBUTTONUP:
			this->dwFlags = MOUSEEVENTF_LEFTUP;
			break;
		case WM_MBUTTONDOWN:
			this->dwFlags = MOUSEEVENTF_MIDDLEDOWN;
			break;
		case WM_MBUTTONUP:
			this->dwFlags = MOUSEEVENTF_MIDDLEUP;
			break;
		case WM_RBUTTONDOWN:
			this->dwFlags = MOUSEEVENTF_RIGHTDOWN;
			break;
		case WM_RBUTTONUP:
			this->dwFlags = MOUSEEVENTF_RIGHTUP;
			break;

		case WM_MOUSEMOVE:
			this->dwFlags = MOUSEEVENTF_MOVE;
			break;

		case WM_MOUSEWHEEL:
			this->dwFlags = MOUSEEVENTF_WHEEL;
			this->mouseData = HIWORD(info->mouseData);
			break;
		case WM_MOUSEHWHEEL:
			this->dwFlags = MOUSEEVENTF_HWHEEL;
			this->mouseData = HIWORD(info->mouseData);
			break;

		case WM_XBUTTONDOWN:
			this->dwFlags = MOUSEEVENTF_XDOWN;
			this->mouseData = HIWORD(info->mouseData);
			break;
		case WM_XBUTTONUP:
			this->dwFlags = MOUSEEVENTF_XUP;
			this->mouseData = HIWORD(info->mouseData);
			break;
		}

		this->dwFlags |= MOUSEEVENTF_ABSOLUTE;
	}
};

