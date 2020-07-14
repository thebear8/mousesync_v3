#include <iostream>
#include "udpClient.h"

struct testStruct
{
	int t = 23;
	float f = 1.12345;
};

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
			testStruct t;
			if (client.receiveObj(t))
			{
				std::cout << "T: " << t.t << "F: " << t.f << "\n";
			}
		}
	}
	else
	{
		std::cout << "Mode: Client\n";

		std::string dstIp;
		std::cin >> dstIp;

		udpClient client(8080, dstIp, 8080);
		testStruct t;

		for (;;)
		{
			client.sendObj(t);
		}
	}
}