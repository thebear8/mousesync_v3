#pragma once
#include <stdint.h>
#include "crc32.h"
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
	uint32_t length, hash, crc32;
};

struct udpRawPacketHeader : udpPacketHeader
{
	udpRawPacketHeader(void* data, int length)
	{
		this->magic = udpPacketHeader_magic;
		this->type = udpPacketType::raw;
		this->length = length;
		this->hash = 0;
		this->crc32 = calculateCRC32(data, length);
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
		this->crc32 = calculateCRC32(&obj, sizeof(T));
	}
};