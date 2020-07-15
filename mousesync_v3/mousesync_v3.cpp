#include <iostream>
#include "udpClient.h"
#include "inputEvent.h"
#include "mouseHook.h"
#include "keyboardHook.h"
#include "inputEventDispatcher.h"
#include "concurrentqueue.h"

LPARAM __stdcall mouseProc(int nCode, WPARAM wp, MSLLHOOKSTRUCT* info);
LPARAM __stdcall keyboardProc(int nCode, WPARAM wp, KBDLLHOOKSTRUCT* info);

mouseHook mHook(mouseProc);
keyboardHook kbHook(keyboardProc);

bool capture = true;
moodycamel::ConcurrentQueue<inputEvent> sendQueue;

LPARAM __stdcall mouseProc(int nCode, WPARAM wp, MSLLHOOKSTRUCT* info)
{
	if (capture)
	{
		if (nCode >= 0)
		{
			auto mEvent = mouseEvent(wp, info);
			auto iEvent = inputEvent(mEvent);
			sendQueue.enqueue(iEvent);
		}

		return 1;
	}
	else
	{
		return CallNextHookEx(mHook.getHook(), nCode, wp, (LPARAM)info);
	}
}

LPARAM __stdcall keyboardProc(int nCode, WPARAM wp, KBDLLHOOKSTRUCT* info)
{
	if (capture)
	{
		if (nCode >= 0)
		{
			auto kbEvent = keyboardEvent(wp, info);
			auto iEvent = inputEvent(kbEvent);
			sendQueue.enqueue(iEvent);
		}

		return 1;
	}
	else
	{
		return CallNextHookEx(kbHook.getHook(), nCode, wp, (LPARAM)info);
	}
}

int main(int argc, char* argv[])
{
	if (argc <= 1)
	{
		return -1;
	}

	auto modeString = std::string(argv[1]);
	if (modeString == "s")
	{
		std::cout << "Mode: Server\n";
		std::string dstIp;
		std::cin >> dstIp;
		udpClient client(8080, dstIp, 8080);

		for (;;)
		{
			inputEvent iEvent;
			if (!client.receiveObj(iEvent))
			{
				Sleep(1);
			}
			else
			{
				inputEventDispatcher::dispatchEvent(iEvent);
			}
		}
	}
	else
	{
		std::cout << "Mode: Client\n";
		std::string dstIp;
		std::cin >> dstIp;
		udpClient client(8080, dstIp, 8080);

		for (;;)
		{
			inputEvent iEvent;
			if (!sendQueue.try_dequeue(iEvent))
			{
				Sleep(1);
			}
			else
			{
				client.sendObj(iEvent);
			}
		}
	}
}