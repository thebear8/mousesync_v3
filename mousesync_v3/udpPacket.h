#pragma once
#include <stdint.h>
#include "typeHasher.h"

const uint64_t udpPacketHeader_magic = 0xC0FFEEBADBAD;

enum class udpPacketType
{
	raw,
	obj
};

struct udpPacketHeader
{
	uint64_t magic;
	udpPacketType type;
	uint32_t length, hash;
};

struct udpRawPacketHeader : udpPacketHeader
{
	udpRawPacketHeader(void* data, int length)
	{
		this->magic = udpPacketHeader_magic;
		this->type = udpPacketType::raw;
		this->length = length;
		this->hash = 0;
	}
};

template<class T>
struct udpObjPacketHeader : udpPacketHeader
{
	udpObjPacketHeader(T& obj)
	{
		this->magic = udpPacketHeader_magic;
		this->type = udpPacketType::obj;
		this->length = sizeof(T);
		this->hash = typeHasher::getHash<T>();
	}
};