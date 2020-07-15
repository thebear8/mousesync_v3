#include "inputEventDispatcher.h"

void dispatchMouse(mouseEvent& mEvent)
{
	INPUT input = { 0 };
	input.mi = mEvent;
	input.type = INPUT_MOUSE;
	SendInput(1, &input, sizeof(input));
}

void dispatchKeyboard(keyboardEvent& kbEvent)
{
	INPUT input = { 0 };
	input.ki = kbEvent;
	input.type = INPUT_KEYBOARD;
	SendInput(1, &input, sizeof(input));
}

void inputEventDispatcher::dispatchEvent(inputEvent& iEvent)
{
	switch (iEvent.type)
	{
	case inputEventType::mouse:
		dispatchMouse(iEvent.mouse);
		break;
	case inputEventType::keyboard:
		dispatchKeyboard(iEvent.keyboard);
		break;
	case inputEventType::management:
		break;
	default:
		break;
	}
}