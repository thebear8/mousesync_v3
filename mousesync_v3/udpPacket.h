#pragma once
#include <stdint.h>
#include "crc32.h"

const uint64_t udpPacketHeader_magic = 0xC0FFEEBADBAD;

class udpPacketHeader
{
	uint64_t magic;
	bool isRaw;
	uint32_t length, typeHash, crc32;
};

class udpPacketObj
{

};
