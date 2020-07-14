#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")

#include "typeHasher.h"
#include "crc32.h"
#include "udpPacket.h"

const static bool __unused_static_initializer = []()
{
	WSADATA data;
	WSAStartup(MAKEWORD(2, 2), &data);

	return true;
}();

template<class T>
class udpObjHeader
{
public:
	size_t typeHash;
	size_t typeSize;

	udpObjHeader()
	{
		this->typeHash = typeHasher::getHash<T>();
		this->typeSize = sizeof(T);
	}

	bool operator==(udpObjHeader other)
	{
		return this->typeHash == other.typeHash && this->typeSize == other.typeSize;
	}

	bool operator!=(udpObjHeader other)
	{
		return !(*this == other);
	}
};

class udpClient
{
private:
	SOCKET socket;
	sockaddr_in src = { 0 }, dst = { 0 };

public:
	udpClient(int srcPort, std::string dstIp, int dstPort)
	{
		src.sin_family = AF_INET;
		dst.sin_family = AF_INET;
		src.sin_port = htons(srcPort);
		dst.sin_port = htons(dstPort);
		inet_pton(AF_INET, "0.0.0.0", &src.sin_addr.s_addr);
		inet_pton(AF_INET, dstIp.c_str(), &dst.sin_addr.s_addr);
		socket = WSASocketW(AF_INET, SOCK_DGRAM, IPPROTO_UDP, 0, 0, 0);

		bind(socket, (sockaddr*)&src, sizeof(src));
	}

	template<class T>
	bool sendObj(T& obj)
	{
		udpObjPacketHeader<T> header(obj);
		int headerBytes, objBytes;
		if (!sendRaw(&header, sizeof(header), &headerBytes) || headerBytes != sizeof(header))
		{
			return false;
		}
		if (!sendRaw(&obj, sizeof(obj), &objBytes) || objBytes != sizeof(obj))
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	template<class T>
	bool receiveObj(T& obj)
	{
		udpObjPacketHeader<T> header(obj), realHeader(obj);
		int headerBytes, objBytes;
		if (!receiveRaw(&header, sizeof(header), &headerBytes) || headerBytes != sizeof(header))
		{
			return false;
		}
		else if (header.type != realHeader.type || header.hash != realHeader.hash || header.length != realHeader.length || header.type != realHeader.type)
		{
			return false;
		}
		else if(!receiveRaw(&obj, sizeof(T), &objBytes) || objBytes != sizeof(T))
		{
			return false;
		}
		else if (header.crc32 != calculateCRC32(&obj, sizeof(T)))
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	bool sendRaw(void* buffer, int length)
	{
		int bytesSent;
		return sendRaw(buffer, length, &bytesSent);
	}

	bool sendRaw(void* buffer, int length, int* bytesSent)
	{
		*bytesSent = sendto(socket, (char*)buffer, length, 0, (sockaddr*)&dst, sizeof(dst));
		return *bytesSent != SOCKET_ERROR;
	}

	bool receiveRaw(void* buffer, int length)
	{
		int bytesReceived;
		return receiveRaw(buffer, length, &bytesReceived);
	}

	bool receiveRaw(void* buffer, int length, int* bytesReceived)
	{
		*bytesReceived = recvfrom(socket, (char*)buffer, length, 0, 0, 0);
		return *bytesReceived != SOCKET_ERROR;
	}
};

