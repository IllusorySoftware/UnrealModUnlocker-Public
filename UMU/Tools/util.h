#pragma once
#include "../Other/global.h"
#include <iostream>
#include <fstream>


#undef max
#define M_PI 3.14159265358979323846f

namespace Util
{



	static uintptr_t SigScanner(uintptr_t start, size_t length, const unsigned char* pattern, const char* mask)
	{
		size_t position = 0;
		auto maskLen = std::strlen(mask) - 1;

		auto StartAdress = start;
		for (auto iterator = StartAdress; iterator < StartAdress + length; ++iterator)
		{
			if (*reinterpret_cast<unsigned char*>(iterator) == pattern[position] || mask[position] == '?')
			{
				if (mask[position + 1] == '\0')
				{
					return iterator - maskLen;
				}

				position++;
			}
			else
			{
				position = 0;
			}
		}

		return -1;
	}
	static uintptr_t StartSigScanner(HMODULE module, const unsigned char* pattern, const char* mask)
	{
		MODULEINFO info = { };
		GetModuleInformation(GetCurrentProcess(), module, &info, sizeof(MODULEINFO));

		return SigScanner(reinterpret_cast<uintptr_t>(module), info.SizeOfImage, pattern, mask);
	}

	
}