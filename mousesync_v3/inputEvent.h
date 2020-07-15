#pragma once
#include "mouseEvent.h"
#include "keyboardEvent.h"

enum class inputEventType
{
	mouse,
	keyboard,
	management
};

struct inputEvent
{
	mouseEvent mouse;
	keyboardEvent keyboard;
	inputEventType type;

	inputEvent(keyboardEvent kbEvent)
	{
		this->keyboard = kbEvent;
		this->type = inputEventType::keyboard;
	}

	inputEvent(mouseEvent mEvent)
	{
		this->mouse = mEvent;
		this->type = inputEventType::mouse;
	}
};