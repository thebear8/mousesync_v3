#pragma once
#include <stdint.h>
#include <functional>
#include <string>

class typeHasher
{
private:
	static std::hash<std::string> hash;

public:
	template<class T>
	static size_t getHash()
	{
		return hash(typeid(T).name());
	}
};

