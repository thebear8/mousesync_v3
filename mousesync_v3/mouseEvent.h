#pragma once
#include <Windows.h>

enum class mouseEventType
{
	lButtonDown,
	lButtonUp,
	rButtonDown,
	rButtonUp,
	xButton1Down,
	xButton1Up,
	xButton2Down,
	xButton2Up,

	move,
	wheel,
	hWheel,

	unknown,
};

struct mouseEvent
{
	float x, y;
	DWORD wheelDelta;
	mouseEventType type;

	mouseEvent()
	{
		this->x = 0;
		this->y = 0;
		this->wheelDelta = 0;
		this->type = mouseEventType::unknown;
	}

	mouseEvent(MSLLHOOKSTRUCT* info, DWORD type)
	{
		this->x = ((float)info->pt.x) / ((float)GetSystemMetrics(SM_CXSCREEN));
		this->y = ((float)info->pt.y) / ((float)GetSystemMetrics(SM_CYSCREEN));
		this->wheelDelta = 0;

		switch (type)
		{
		case WM_LBUTTONDOWN:
			this->type = mouseEventType::lButtonDown;
			break;
		case WM_LBUTTONUP:
			this->type = mouseEventType::lButtonUp;
			break;
		case WM_MOUSEMOVE:
			this->type = mouseEventType::move;
			break;
		case WM_MOUSEWHEEL:
			this->type = mouseEventType::wheel;
			this->wheelDelta = HIWORD(info->mouseData);
			break;
		case WM_MOUSEHWHEEL:
			this->type = mouseEventType::hWheel;
			this->wheelDelta = HIWORD(info->mouseData);
			break;
		case WM_RBUTTONDOWN:
			this->type = mouseEventType::rButtonDown;
			break;
		case WM_RBUTTONUP:
			this->type = mouseEventType::rButtonUp;
			break;
		case WM_XBUTTONDOWN:
			if (HIWORD(info->mouseData) == XBUTTON1)
			{
				this->type = mouseEventType::xButton1Down;
			}
			else if (HIWORD(info->mouseData) == XBUTTON2)
			{
				this->type = mouseEventType::xButton2Down;
			}
			else
			{
				this->type = mouseEventType::unknown;
			}
			break;
		case WM_XBUTTONUP:
			if (HIWORD(info->mouseData) == XBUTTON1)
			{
				this->type = mouseEventType::xButton1Up;
			}
			else if (HIWORD(info->mouseData) == XBUTTON2)
			{
				this->type = mouseEventType::xButton2Up;
			}
			else
			{
				this->type = mouseEventType::unknown;
			}
			break;
		default:
			this->type = mouseEventType::unknown;
			break;
		}
	}
};

