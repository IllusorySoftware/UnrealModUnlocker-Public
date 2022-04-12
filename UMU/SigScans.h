#pragma once
#include "util.h"
#include "Pattern.h"


namespace SigScans
{

	//Special Case games that need their own sigs or hooks
	bool bSpecialCaseGame = false;
	std::string GameName;
	bool DQXI_S = false;
	std::string DQXISGame = "DRAGON QUEST XI S";
	std::string DQXISGameDemo = "DRAGON QUEST XI S Demo"; // removed support for this for now.
	//-------------------------------------------------------------------------------------------------------- END


	bool bNoIsNonPakFileNameAllowed = false;
	uintptr_t pakFileFindAddr = -1;
	uintptr_t IsNonPakFileNameAllowedAddr = -1;



	//Find pakFileFindAddr START
	int Get_addr_Pakfile__Find()
	{

		if (pakFileFindAddr == -1)
		{
			//variables 4.22
			char pattern4_22[] = "\x48\x89\x5C\x24\x20\x55\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8D\x6C\x24\xD9\x48\x81\xEC\xD0\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x45\x17\x4C\x8B\xE2\x49\x8B\xF0\x48\x8D\x91\xE8\x00\x00\x00\x4C\x8B\xE9\x49\x8B\xCC\x41\xB8\x01\x00\x00\x00\xE8\x00\x00\x00\x00\x84\xC0\x0F\x84\x00\x00\x00\x00\x49\x8B\xD4\x48\x8D\x4D\xA7\xE8\x00\x00\x00\x00\x41\x80\xBD\xA2\x01\x00\x00\x00\x0F\x84\x00\x00\x00\x00\x8B\x5D\xAF\x45\x33\xF6\x44\x8D\x4B\xFF\x85\xDB\x75\x03\x45\x8B\xCE";
			const char* mask4_22 = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxx????xxxxxxxx????xxxxxxxxxx????xxxxxxxxxxxxxxxxx";


			//Run pattern scan
			pakFileFindAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern4_22), mask4_22);

			if (pakFileFindAddr != -1)
			{
				bNoIsNonPakFileNameAllowed = false;
				return pakFileFindAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}
		
		//Check next version (SPECIAL CASE)
		if (pakFileFindAddr == -1)
		{

			//variables 4.18 DQXI S
			char pattern4_18DQXIS[] = "\x48\x8B\xC4\x4C\x89\x40\x18\x55\x53\x48\x8D\x68\xA1\x48\x81\xEC\x00\x00\x00\x00\x44\x8B\x0D\x00\x00\x00\x00\x33\xDB\x48\x89\x70\x10\x8B\xF3\x48\x89\x78\xE8\x48\x8B\xF9\x4C\x89\x60\xE0\x4C\x89\x70\xD0\x4C\x8B\xF2\x65\x48\x8B\x04\x25\x00\x00\x00\x00\xB9\x00\x00\x00\x00\x48\x89\x5D\x0F\x89\x5D\x1B\x4E\x8B\x0C\xC8\x42\x8B\x04\x09\x39\x05\x00\x00\x00\x00\x0F\x8F\x00\x00\x00\x00";
			const char* mask4_18DQXIS = "xxxxxxxxxxxxxxxx????xxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????x????xxxxxxxxxxxxxxxxx????xx????";

			//Run pattern scan 4.18 DQXI S
			pakFileFindAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern4_18DQXIS), mask4_18DQXIS);

			if (pakFileFindAddr != NULL && (GameName == DQXISGame || GameName == DQXISGameDemo))
			{
				bSpecialCaseGame = true;
				DQXI_S = true;
				bNoIsNonPakFileNameAllowed = false;
				return pakFileFindAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}

		}



		//Next Version Scan
		if (pakFileFindAddr == -1)
		{

			//variables 4.21
			char pattern4_21[] = "\x40\x55\x53\x56\x57\x41\x54\x41\x56\x41\x57\x48\x8D\x6C\x24\xD9\x48\x81\xEC\xD0\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x45\x17\x4C\x8B\xE2\x49\x8B\xD8\x48\x8D\x91\xD8\x00\x00\x00\x4C\x8B\xF1\x49\x8B\xCC\x41\xB8\x01\x00\x00\x00\xE8\x00\x00\x00\x00\x84\xC0\x0F\x84\x00\x00\x00\x00\x49\x8B\xD4\x48\x8D\x4D\x9F\xE8\x00\x00\x00\x00\x41\x80\xBE\x92\x01\x00\x00\x00\x0F\x84\x00\x00\x00\x00\x8B\x75\xA7\x33\xFF\x8D\x4E\xFF\x85\xF6\x75\x02\x8B\xCF";
			const char* mask4_21 = "xxxxxxxxxxxxxxxxxxxxxxxxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxx????xxxxxxxx????xxxxxxxxxx????xxxxxxxxxxxxxx";


			//Run pattern scan
			pakFileFindAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern4_21), mask4_21);

			if (pakFileFindAddr != -1)
			{
				bNoIsNonPakFileNameAllowed = false;
				return pakFileFindAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}


		//Next Version Scan
		if (pakFileFindAddr == -1)
		{

			//variables 4.18
			char pattern4_18[] = "\x48\x89\x5C\x24\x20\x56\x57\x41\x57\x48\x83\xEC\x50\x48\x8B\xF2\x45\x33\xFF\x48\x8B\xF9\x48\x8D\x91\xC8\x00\x00\x00\x48\x8B\xCE\x41\x8B\xDF\x45\x8D\x47\x01\xE8\x00\x00\x00\x00\x84\xC0\x0F\x84\x00\x00\x00\x00\x48\x89\x6C\x24\x78\x48\x8D\x4C\x24\x20\x48\x8B\xD6\x4C\x89\xB4\x24\x80\x00\x00\x00\xE8\x00\x00\x00\x00\x39\x5C\x24\x28\x4C\x8D\x35\x00\x00\x00\x00\x49\x8B\xD6\x48\x8B\xCF\x48\x0F\x45\x54\x24\x20\xE8\x00\x00\x00\x00\x48\x8B\xE8\x48\x85\xC0\x0F\x84\x00\x00\x00\x00\x8B\x4C\x24\x28\x85\xC9\x74\x04\xFF\xC9\xEB\x03";
			const char* mask4_18 = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxx????xxxxxxxxxxxxxxxxxxxxxx????xxxxxxx????xxxxxxxxxxxxx????xxxxxxxx????xxxxxxxxxxxx";


			//Run pattern scan
			pakFileFindAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern4_18), mask4_18);

			if (pakFileFindAddr != -1)
			{
				bNoIsNonPakFileNameAllowed = false;
				return pakFileFindAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}


		//Next Version Scan
		if (pakFileFindAddr == -1)
		{

			//variables 4.20
			char pattern4_20[] = "\x48\x89\x5C\x24\x10\x48\x89\x6C\x24\x18\x56\x57\x41\x54\x41\x56\x41\x57\x48\x83\xEC\x60\x48\x8B\xDA\x49\x8B\xF8\x48\x8D\x91\xC8\x00\x00\x00\x48\x8B\xE9\x48\x8B\xCB\x41\xB8\x01\x00\x00\x00\xE8\x00\x00\x00\x00\x84\xC0\x0F\x84\x00\x00\x00\x00\x48\x8B\xD3\x48\x8D\x4C\x24\x30\xE8\x00\x00\x00\x00\x80\xBD\x7A\x01\x00\x00\x00\x0F\x84\x00\x00\x00\x00\x8B\x44\x24\x38\x33\xF6\x8D\x50\xFF\x85\xC0\x75\x02\x8B\xD6";
			const char* mask4_20 = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxx????xxxxxxxxx????xxxxxxxxx????xxxxxxxxxxxxxxx";


			//Run pattern scan
			pakFileFindAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern4_20), mask4_20);

			if (pakFileFindAddr != -1)
			{
				bNoIsNonPakFileNameAllowed = false;
				return pakFileFindAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}

		//Next Version Scan
		if (pakFileFindAddr == -1)
		{

			//variables 4.20.2.0 Tropico6
			char pattern[] = "\x48\x89\x5C\x24\x00\x55\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x83\xEC\x50\x4C\x8B\xEA\x49\x8B\xF8\x48\x8D\x91\x00\x00\x00\x00\x48\x8B\xE9\x49\x8B\xCD\x41\xB8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x84\xC0\x0F\x84\x00\x00\x00\x00\x49\x8B\xD5\x48\x8D\x4C\x24\x00\xE8\x00\x00\x00\x00\x80\xBD\x00\x00\x00\x00\x00\x0F\x84\x00\x00\x00\x00\x8B\x4C\x24\x38\x33\xF6\x44\x8D\x51\xFF\x85\xC9\x75\x03\x44\x8B\xD6";
			const char* mask = "xxxx?xxxxxxxxxxxxxxxxxxxxxxxx????xxxxxxxx????x????xxxx????xxxxxxx?x????xx?????xx????xxxxxxxxxxxxxxxxx";


			//Run pattern scan
			pakFileFindAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern), mask);

			if (pakFileFindAddr != -1)
			{
				bNoIsNonPakFileNameAllowed = false;
				return pakFileFindAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}


		//Next Version Scan
		if (pakFileFindAddr == -1)
		{

			//variables 4.19
			char pattern4_19[] = "\x48\x89\x5C\x24\x20\x56\x57\x41\x57\x48\x83\xEC\x50\x48\x8B\xF2\x45\x33\xFF\x48\x8B\xF9\x48\x8D\x91\xC8\x00\x00\x00\x48\x8B\xCE\x41\x8B\xDF\x45\x8D\x47\x01\xE8\x00\x00\x00\x00\x84\xC0\x0F\x84\x00\x00\x00\x00\x48\x89\x6C\x24\x78\x48\x8D\x4C\x24\x20\x48\x8B\xD6\x4C\x89\xB4\x24\x80\x00\x00\x00\xE8\x00\x00\x00\x00\x39\x5C\x24\x28\x4C\x8D\x35\x00\x00\x00\x00\x49\x8B\xD6\x48\x8B\xCF\x48\x0F\x45\x54\x24\x20\xE8\x00\x00\x00\x00\x48\x8B\xE8\x48\x85\xC0\x0F\x84\x00\x00\x00\x00\x8B\x4C\x24\x28\x85\xC9\x74\x04\xFF\xC9\xEB\x03";
			const char* mask4_19 = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxx????xxxxxxxxxxxxxxxxxxxxxx????xxxxxxx????xxxxxxxxxxxxx????xxxxxxxx????xxxxxxxxxxxx";


			//Run pattern scan
			pakFileFindAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern4_19), mask4_19);

			if (pakFileFindAddr != -1)
			{
				bNoIsNonPakFileNameAllowed = false;
				return pakFileFindAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}


		//Next Version Scan
		if (pakFileFindAddr == -1)
		{

			//variables 4.17
			char pattern4_17[] = "\x48\x89\x5C\x24\x20\x56\x57\x41\x57\x48\x83\xEC\x50\x48\x8B\xF2\x45\x33\xFF\x48\x8B\xF9\x48\x8D\x91\xC8\x00\x00\x00\x48\x8B\xCE\x41\x8B\xDF\x45\x8D\x47\x01\xE8\x00\x00\x00\x00\x84\xC0\x0F\x84\x00\x00\x00\x00\x48\x89\x6C\x24\x78\x48\x8D\x4C\x24\x20\x48\x8B\xD6\x4C\x89\xB4\x24\x80\x00\x00\x00\xE8\x00\x00\x00\x00\x39\x5C\x24\x28\x4C\x8D\x35\x00\x00\x00\x00\x49\x8B\xD6\x48\x8B\xCF\x48\x0F\x45\x54\x24\x20\xE8\x00\x00\x00\x00\x48\x8B\xE8\x48\x85\xC0\x0F\x84\x00\x00\x00\x00\x8B\x4C\x24\x28\x85\xC9\x74\x04\xFF\xC9\xEB\x03";
			const char* mask4_17 = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxx????xxxxxxxxxxxxxxxxxxxxxx????xxxxxxx????xxxxxxxxxxxxx????xxxxxxxx????xxxxxxxxxxxx";


			//Run pattern scan
			pakFileFindAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern4_17), mask4_17);

			if (pakFileFindAddr != -1)
			{
				bNoIsNonPakFileNameAllowed = false;
				return pakFileFindAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}


		//Next Version Scan
		if (pakFileFindAddr == -1)
		{

			//variables 4.16
			char pattern4_16[] = "\x48\x89\x5C\x24\x18\x48\x89\x6C\x24\x20\x56\x57\x41\x57\x48\x83\xEC\x50\x48\x8B\xF2\x48\x8D\xB9\xC8\x00\x00\x00\x45\x33\xFF\x48\x8B\xE9\x48\x8B\xD7\x48\x8B\xCE\x41\x8B\xDF\x45\x8D\x47\x01\xE8\x00\x00\x00\x00\x84\xC0\x0F\x84\x00\x00\x00\x00\x48\x8B\xD6\x4C\x89\x74\x24\x78\x48\x8D\x4C\x24\x20\xE8\x00\x00\x00\x00\x39\x5C\x24\x28\x4C\x8D\x35\x00\x00\x00\x00\x49\x8B\xD6\x48\x8B\xCD\x48\x0F\x45\x54\x24\x20\xE8\x00\x00\x00\x00\x48\x8B\xE8\x48\x85\xC0\x0F\x84\x00\x00\x00\x00\x8B\x57\x08\x85\xD2\x74\x04\xFF\xCA\xEB\x03";
			const char* mask4_16 = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxx????xxxxxxxxxxxxxx????xxxxxxx????xxxxxxxxxxxxx????xxxxxxxx????xxxxxxxxxxx";


			//Run pattern scan
			pakFileFindAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern4_16), mask4_16);

			if (pakFileFindAddr != -1)
			{
				bNoIsNonPakFileNameAllowed = false;
				return pakFileFindAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}


		//Next Version Scan
		if (pakFileFindAddr == -1)
		{

			//variables 4.15
			char pattern4_15[] = "\x48\x89\x5C\x24\x18\x48\x89\x6C\x24\x20\x56\x57\x41\x57\x48\x83\xEC\x40\x48\x8B\xFA\x48\x8D\xB1\xC8\x00\x00\x00\x45\x33\xFF\x48\x8B\xE9\x48\x8B\xD6\x48\x8B\xCF\x41\x8B\xDF\x45\x8D\x47\x01\xE8\x00\x00\x00\x00\x84\xC0\x0F\x84\x00\x00\x00\x00\x48\x8B\xD7\x4C\x89\x74\x24\x68\x48\x8D\x4C\x24\x30\xE8\x00\x00\x00\x00\x39\x5C\x24\x38\x4C\x8D\x35\x00\x00\x00\x00\x49\x8B\xD6\x48\x8B\xCD\x48\x0F\x45\x54\x24\x30\xE8\x00\x00\x00\x00\x48\x8B\xE8\x48\x85\xC0\x0F\x84\x00\x00\x00\x00\x8B\x4E\x08\x85\xC9\x74\x04\xFF\xC9\xEB\x03";
			const char* mask4_15 = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxx????xxxxxxxxxxxxxx????xxxxxxx????xxxxxxxxxxxxx????xxxxxxxx????xxxxxxxxxxx";


			//Run pattern scan
			pakFileFindAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern4_15), mask4_15);

			if (pakFileFindAddr != -1)
			{
				bNoIsNonPakFileNameAllowed = false;
				return pakFileFindAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}


		//Next Version Scan
		if (pakFileFindAddr == -1)
		{

			//variables 4.14
			char pattern4_14[] = "\x48\x89\x5C\x24\x18\x48\x89\x6C\x24\x20\x56\x57\x41\x57\x48\x83\xEC\x40\x48\x8B\xFA\x48\x8D\xB1\xC8\x00\x00\x00\x45\x33\xFF\x48\x8B\xE9\x48\x8B\xD6\x48\x8B\xCF\x41\x8B\xDF\x45\x8D\x47\x01\xE8\x00\x00\x00\x00\x84\xC0\x0F\x84\x00\x00\x00\x00\x48\x8B\xD7\x4C\x89\x74\x24\x68\x48\x8D\x4C\x24\x30\xE8\x00\x00\x00\x00\x39\x5C\x24\x38\x4C\x8D\x35\x00\x00\x00\x00\x49\x8B\xD6\x48\x8B\xCD\x48\x0F\x45\x54\x24\x30\xE8\x00\x00\x00\x00\x48\x8B\xE8\x48\x85\xC0\x0F\x84\x00\x00\x00\x00\x8B\x4E\x08\x85\xC9\x74\x04\xFF\xC9\xEB\x03";
			const char* mask4_14 = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxx????xxxxxxxxxxxxxx????xxxxxxx????xxxxxxxxxxxxx????xxxxxxxx????xxxxxxxxxxx";


			//Run pattern scan
			pakFileFindAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern4_14), mask4_14);

			if (pakFileFindAddr != -1)
			{
				bNoIsNonPakFileNameAllowed = false;
				return pakFileFindAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}


		//Next Version Scan
		if (pakFileFindAddr == -1)
		{

			//variables 4.24.x
			char pattern4_24[] = "\x48\x89\x5C\x24\x20\x55\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8D\x6C\x24\xB0\x48\x81\xEC\x50\x01\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x45\x40\x66\x0F\x6F\x05\x00\x00\x00\x00\x4C\x8D\x4D\xF0\x33\xFF\x66\x0F\x7F\x45\xF0\x49\x8B\xD8\x48\x89\x4D\x80\x0F\x57\xC0\x48\x89\x7D\x00\x48\x8B\xF2\x48\x89\x7D\x20\x33\xC0\x48\x89\x7D\x28\x4C\x8D\x44\x24\x48\x48\x89\x7D\x30\x48\x8B\xD3\x66\x89\x7D\x38\x0F\x11\x45\x08\x4C\x8B\xE9\x89\x45\x18\x48\x89\x7C\x24\x48\xE8\x00\x00\x00\x00\x4C\x8D\x77\xFF\x84\xC0\x0F\x84\x00\x00\x00\x00\x48\x89\x7C\x24\x58";
			const char* mask4_24 = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxxxxxxxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxxxxxx????xxxxx";


			//Run pattern scan
			pakFileFindAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern4_24), mask4_24);

			if (pakFileFindAddr != -1)
			{
				bNoIsNonPakFileNameAllowed = false;
				return pakFileFindAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}

		//Next Version Scan
		if (pakFileFindAddr == -1)
		{

			//variables 4.24.3
			char pattern[] = "\x48\x89\x5C\x24\x00\x55\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8D\x6C\x24\x00\x48\x81\xEC\x00\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x45\x17\x4C\x8B\xEA\x49\x8B\xF0\x48\x8D\x91\x00\x00\x00\x00\x4C\x8B\xF9\x49\x8B\xCD\x41\xB8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x84\xC0\x0F\x84\x00\x00\x00\x00\x49\x8B\xD5\x48\x8D\x4D\xA7\xE8\x00\x00\x00\x00\x41\x80\xBF\x00\x00\x00\x00\x00\x0F\x84\x00\x00\x00\x00\x8B\x5D\xAF\x45\x33\xF6\x8D\x53\xFF\x85\xDB\x75\x03\x41\x8B\xD6";
			const char* mask = "xxxx?xxxxxxxxxxxxxxx?xxx????xxx????xxxxxxxxxxxxxxxx????xxxxxxxx????x????xxxx????xxxxxxxx????xxx?????xx????xxxxxxxxxxxxxxxx";


			//Run pattern scan
			pakFileFindAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern), mask);

			if (pakFileFindAddr != -1)
			{
				bNoIsNonPakFileNameAllowed = false;
				return pakFileFindAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}


		//Next Version Scan
		if (pakFileFindAddr == -1)
		{

			//variables 4.25.3
			char pattern4_25_3[] = "\x48\x89\x5C\x24\x00\x55\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8D\x6C\x24\x00\x48\x81\xEC\x00\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x45\x17\x4C\x8B\xE2\x49\x8B\xD8\x48\x8D\x91\x00\x00\x00\x00\x4C\x8B\xF1\x49\x8B\xCC\x41\xB8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x84\xC0\x0F\x84\x00\x00\x00\x00\x49\x8B\xD4\x48\x8D\x4D\xAF\xE8\x00\x00\x00\x00\x41\x80\xBE\x00\x00\x00\x00\x00\x0F\x84\x00\x00\x00\x00\x8B\x75\xB7\x33\xFF\x44\x8D\x46\xFF\x85\xF6\x75\x03\x44\x8B\xC7";
			const char* mask4_25_3 = "xxxx?xxxxxxxxxxxxxxx?xxx????xxx????xxxxxxxxxxxxxxxx????xxxxxxxx????x????xxxx????xxxxxxxx????xxx?????xx????xxxxxxxxxxxxxxxx";


			//Run pattern scan
			pakFileFindAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern4_25_3), mask4_25_3);

			if (pakFileFindAddr != -1)
			{
				bNoIsNonPakFileNameAllowed = false;
				return pakFileFindAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}


		//Next Version Scan
		if (pakFileFindAddr == -1)
		{

			//variables 4.25.2
			char pattern4_25_2[] = "\x48\x89\x5C\x24\x00\x55\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8D\x6C\x24\x00\x48\x81\xEC\x00\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x45\x17\x4C\x8B\xE2\x48\x89\x4D\xA7\x48\x8D\x91\x00\x00\x00\x00\x49\x8B\xF0\x48\x8B\xF9\xBB\x00\x00\x00\x00\x44\x8B\xC3\x49\x8B\xCC\xE8\x00\x00\x00\x00\x84\xC0\x0F\x84\x00\x00\x00\x00\x49\x8B\xD4\x48\x8D\x4D\xAF\xE8\x00\x00\x00\x00\x80\xBF\x00\x00\x00\x00\x00\x0F\x84\x00\x00\x00\x00\x8B\x5D\xB7\x45\x33\xF6\x8D\x53\xFF\x85\xDB\x75\x03\x41\x8B\xD6";
			const char* mask4_25_2 = "xxxx?xxxxxxxxxxxxxxx?xxx????xxx????xxxxxxxxxxxxxxxxx????xxxxxxx????xxxxxxx????xxxx????xxxxxxxx????xx?????xx????xxxxxxxxxxxxxxxx";


			//Run pattern scan
			pakFileFindAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern4_25_2), mask4_25_2);

			if (pakFileFindAddr != -1)
			{
				bNoIsNonPakFileNameAllowed = false;
				return pakFileFindAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}


		//Next Version Scan
		if (pakFileFindAddr == -1)
		{

			//variables 4.26.0
			char pattern4_26[] = "\x48\x89\x5C\x24\x00\x48\x89\x6C\x24\x00\x48\x89\x74\x24\x00\x57\x41\x56\x41\x57\x48\x83\xEC\x30\x80\xB9\x00\x00\x00\x00\x00\x48\x8B\xFA\x48\x8D\x91\x00\x00\x00\x00\x4D\x8B\xF8\x48\x8B\xD9\x0F\x84\x00\x00\x00\x00\x8B\xA9\x00\x00\x00\x00\x41\xB8\x00\x00\x00\x00\x4C\x8B\xB1\x00\x00\x00\x00\x48\x8B\xCF\xE8\x00\x00\x00\x00\x84\xC0\x0F\x84\x00\x00\x00\x00\x83\x7F\x08\x00\x74\x05\x48\x8B\x17\xEB\x07";
			const char* mask4_26 = "xxxx?xxxx?xxxx?xxxxxxxxxxx?????xxxxxx????xxxxxxxx????xx????xx????xxx????xxxx????xxxx????xxxxxxxxxxx";


			//Run pattern scan
			pakFileFindAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern4_26), mask4_26);

			if (pakFileFindAddr != -1)
			{
				bNoIsNonPakFileNameAllowed = false;
				return pakFileFindAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}


		//Next Version Scan
		if (pakFileFindAddr == -1)
		{

			//variables 4.13
			char pattern4_13[] = "\x48\x89\x5C\x24\x00\x48\x89\x6C\x24\x00\x56\x57\x41\x57\x48\x83\xEC\x40\x48\x8B\xFA\x48\x8D\xB1\x00\x00\x00\x00\x45\x33\xFF\x48\x8B\xE9\x48\x8B\xD6\x48\x8B\xCF\x41\x8B\xDF\x45\x8D\x47\x01\xE8\x00\x00\x00\x00\x84\xC0\x0F\x84\x00\x00\x00\x00\x48\x8B\xD7";
			const char* mask4_13 = "xxxx?xxxx?xxxxxxxxxxxxxx????xxxxxxxxxxxxxxxxxxxx????xxxx????xxx";


			//Run pattern scan
			pakFileFindAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern4_13), mask4_13);

			if (pakFileFindAddr != -1)
			{
				bNoIsNonPakFileNameAllowed = false;
				return pakFileFindAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}


		//Next Version Scan
		if (pakFileFindAddr == -1)
		{

			//variables 4.12
			char pattern4_12[] = "\x48\x89\x5C\x24\x00\x48\x89\x6C\x24\x00\x56\x57\x41\x57\x48\x83\xEC\x40\x48\x8B\xFA\x48\x8D\xB1\x00\x00\x00\x00\x45\x33\xFF\x48\x8B\xE9\x48\x8B\xD6\x48\x8B\xCF\x41\x8B\xDF\x45\x8D\x47\x01\xE8\x00\x00\x00\x00\x84\xC0\x0F\x84\x00\x00\x00\x00\x48\x8B\xD7";
			const char* mask4_12 = "xxxx?xxxx?xxxxxxxxxxxxxx????xxxxxxxxxxxxxxxxxxxx????xxxx????xxx";
			

			//Run pattern scan
			pakFileFindAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern4_12), mask4_12);

			if (pakFileFindAddr != -1)
			{
				bNoIsNonPakFileNameAllowed = false;
				return pakFileFindAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}


	
		//Next Version Scan
		if (pakFileFindAddr == -1)
		{

			//variables 4.12.5 NewRetroArcade
			char pattern4_12_NRA[] = "\x48\x89\x5C\x24\x00\x48\x89\x6C\x24\x00\x56\x57\x41\x57\x48\x83\xEC\x50\x48\x8B\xF2\x48\x8D\xB9\x00\x00\x00\x00\x45\x33\xFF\x48\x8B\xE9\x48\x8B\xD7\x48\x8B\xCE\x41\x8B\xDF\x45\x8D\x47\x01\xE8\x00\x00\x00\x00\x84\xC0\x0F\x84\x00\x00\x00\x00\x48\x8B\xD6\x4C\x89\x74\x24\x00\x48\x8D\x4C\x24\x00\xE8\x00\x00\x00\x00\x39\x5C\x24\x28\x4C\x8D\x35\x00\x00\x00\x00\x49\x8B\xD6\x48\x8B\xCD\x48\x0F\x45\x54\x24\x00\xE8\x00\x00\x00\x00\x48\x8B\xE8\x48\x85\xC0\x0F\x84\x00\x00\x00\x00\x8B\x57\x08\x85\xD2\x74\x04\xFF\xCA\xEB\x03";
			const char* mask4_12_NRA = "xxxx?xxxx?xxxxxxxxxxxxxx????xxxxxxxxxxxxxxxxxxxx????xxxx????xxxxxxx?xxxx?x????xxxxxxx????xxxxxxxxxxx?x????xxxxxxxx????xxxxxxxxxxx";


			//Run pattern scan
			pakFileFindAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern4_12_NRA), mask4_12_NRA);

			if (pakFileFindAddr != -1)
			{
				bNoIsNonPakFileNameAllowed = false;
				return pakFileFindAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}

		//Next Version Scan
		if (pakFileFindAddr == -1)
		{

			//variables 4.21.0 OuterWorlds
			char pattern[] = "\x48\x89\x5C\x24\x00\x55\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8D\x6C\x24\x00\x48\x81\xEC\x00\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x45\x17\x4C\x8B\xE2\x49\x8B\xF8\x48\x8D\x91\x00\x00\x00\x00\x4C\x8B\xE9\x49\x8B\xCC\x41\xB8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x84\xC0\x0F\x84\x00\x00\x00\x00\x49\x8B\xD4\x48\x8D\x4D\xA7\xE8\x00\x00\x00\x00\x41\x80\xBD\x00\x00\x00\x00\x00\x0F\x84\x00\x00\x00\x00\x8B\x5D\xAF\x33\xF6\x44\x8D\x4B\xFF\x85\xDB\x75\x03\x44\x8B\xCE";
			const char* mask = "xxxx?xxxxxxxxxxxxxxx?xxx????xxx????xxxxxxxxxxxxxxxx????xxxxxxxx????x????xxxx????xxxxxxxx????xxx?????xx????xxxxxxxxxxxxxxxx";


			//Run pattern scan
			pakFileFindAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern), mask);

			if (pakFileFindAddr != -1)
			{
				bNoIsNonPakFileNameAllowed = false;
				return pakFileFindAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}


		//Next Version Scan
		if (pakFileFindAddr == -1)
		{

			//variables 4.27.1
			char pattern[] = "\x48\x89\x5C\x24\x00\x48\x89\x6C\x24\x00\x48\x89\x74\x24\x00\x57\x41\x56\x41\x57\x48\x83\xEC\x30\x80\xB9\x00\x00\x00\x00\x00\x4D\x8B\xF8\x48\x8B\xFA\x48\x8B\xD9\x0F\x84\x00\x00\x00\x00\x8B\xA9\x00\x00\x00\x00\x48\x8D\x91\x00\x00\x00\x00\x4C\x8B\xB1\x00\x00\x00\x00\x41\xB8\x00\x00\x00\x00\x48\x8B\xCF\xE8\x00\x00\x00\x00\x84\xC0\x0F\x84\x00\x00\x00\x00\x83\x7F\x08\x00\x74\x05\x48\x8B\x17\xEB\x07";
			const char* mask = "xxxx?xxxx?xxxx?xxxxxxxxxxx?????xxxxxxxxxxx????xx????xxx????xxx????xx????xxxx????xxxx????xxxxxxxxxxx";


			//Run pattern scan
			pakFileFindAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern), mask);

			if (pakFileFindAddr != -1)
			{
				bNoIsNonPakFileNameAllowed = false;
				return pakFileFindAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}

		}


		//Next Version Scan 4.21 Citadel
		if (pakFileFindAddr == -1)
		{

			//variables 4.21 Citadel
			char pattern[] = "\x48\x89\x5C\x24\x00\x55\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8D\x6C\x24\x00\x48\x81\xEC\x00\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x45\x17\x4C\x8B\xE2\x49\x8B\xF8\x48\x8D\x91\x00\x00\x00\x00\x4C\x8B\xE9\x49\x8B\xCC\x41\xB8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x84\xC0\x0F\x84\x00\x00\x00\x00\x49\x8B\xD4\x48\x8D\x4D\x9F\xE8\x00\x00\x00\x00\x41\x80\xBD\x00\x00\x00\x00\x00\x0F\x84\x00\x00\x00\x00\x8B\x5D\xA7\x33\xF6\x44\x8D\x4B\xFF\x85\xDB\x75\x03\x44\x8B\xCE";
			const char* mask = "xxxx?xxxxxxxxxxxxxxx?xxx????xxx????xxxxxxxxxxxxxxxx????xxxxxxxx????x????xxxx????xxxxxxxx????xxx?????xx????xxxxxxxxxxxxxxxx";


			//Run pattern scan
			pakFileFindAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern), mask);

			if (pakFileFindAddr != -1)
			{
				bNoIsNonPakFileNameAllowed = false;
				return pakFileFindAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}

		}


		//Next Version Scan 4.25 Kena
		if (pakFileFindAddr == -1)
		{

			//variables 4.25 Kena
			char pattern[] = "\x40\x55\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8D\x6C\x24\x00\x48\x81\xEC\x00\x00\x00\x00\x48\xC7\x45\x00\x00\x00\x00\x00\x48\x89\x9C\x24\x00\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x45\x17\x49\x8B\xD8\x4C\x8B\xFA\x48\x8B\xF1\x45\x33\xED\x44\x89\x6C\x24\x00\x48\x8D\x91\x00\x00\x00\x00\x45\x8D\x45\x01\x49\x8B\xCF\xE8\x00\x00\x00\x00\x84\xC0\x0F\x84\x00\x00\x00\x00\x49\x8B\xD7\x48\x8D\x4D\x9F\xE8";
			const char* mask = "xxxxxxxxxxxxxxxx?xxx????xxx?????xxxx????xxx????xxxxxxxxxxxxxxxxxxxxxxx?xxx????xxxxxxxx????xxxx????xxxxxxxx";


			//Run pattern scan
			pakFileFindAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern), mask);

			if (pakFileFindAddr != -1)
			{
				bNoIsNonPakFileNameAllowed = false;
				return pakFileFindAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}

		}


		//Next Version Scan
		if (pakFileFindAddr == -1)
		{
			std::cout << "Scanning for FindFileInPakFile version 4.18 BioMutant Style function signature...\n";

			//variables 4.18 BioMutant Style
			char pattern[] = "\x48\x89\x5C\x24\x00\x56\x57\x41\x57\x48\x83\xEC\x50\x48\x8B\xF2\x45\x33\xFF\x48\x8B\xF9\x48\x8D\x91\x00\x00\x00\x00\x48\x8B\xCE\x41\x8B\xDF\x45\x8D\x47\x01\xE8\x00\x00\x00\x00\x84\xC0\x0F\x84\x00\x00\x00\x00\x48\x89\x6C\x24\x00\x48\x8D\x4C\x24\x00\x48\x8B\xD6\x4C\x89\xB4\x24\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x39\x5C\x24\x28\x4C\x8D\x35\x00\x00\x00\x00\x49\x8B\xD6\x48\x8B\xCF\x48\x0F\x45\x54\x24\x00\xE8\x00\x00\x00\x00\x48\x8B\xE8\x48\x85\xC0\x0F\x84\x00\x00\x00\x00\x8B\x4C\x24\x28\x85\xC9\x74\x04\xFF\xC9\xEB\x03";
			const char* mask = "xxxx?xxxxxxxxxxxxxxxxxxxx????xxxxxxxxxxx????xxxx????xxxx?xxxx?xxxxxxx????x????xxxxxxx????xxxxxxxxxxx?x????xxxxxxxx????xxxxxxxxxxxx";


			//Run pattern scan
			pakFileFindAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern), mask);

			if (pakFileFindAddr != -1)
			{
				bNoIsNonPakFileNameAllowed = false;
				return pakFileFindAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}

		}

		//Next Version Scan
		if (pakFileFindAddr == -1)
		{
			std::cout << "Scanning for FindFileInPakFile version 4.16 LIS2 Style function signature...\n";

			//variables 4.16 LIS2 Style
			char pattern[] = "\x48\x89\x5C\x24\x00\x48\x89\x6C\x24\x00\x56\x57\x41\x57\x48\x83\xEC\x50\x48\x89\xD6\x48\x8D\xB9\x00\x00\x00\x00\x45\x31\xFF\x48\x89\xCD\x48\x89\xFA\x48\x89\xF1\x44\x89\xFB\x45\x8D\x47\x01\xE8\x00\x00\x00\x00\x84\xC0\x0F\x84\x00\x00\x00\x00\x48\x89\xF2\x4C\x89\x74\x24\x00\x48\x8D\x4C\x24\x00\xE8\x00\x00\x00\x00\x39\x5C\x24\x28\x4C\x8D\x35\x00\x00\x00\x00";
			const char* mask = "xxxx?xxxx?xxxxxxxxxxxxxx????xxxxxxxxxxxxxxxxxxxx????xxxx????xxxxxxx?xxxx?x????xxxxxxx????";


			//Run pattern scan
			pakFileFindAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern), mask);

			if (pakFileFindAddr != -1)
			{
				bNoIsNonPakFileNameAllowed = false;
				return pakFileFindAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}

		}




		//Start Sigscans of OLD builds with no IsNoPakFileNameAllowed -----------------------------------------------------------
		//Next Version Scan
		if (pakFileFindAddr == -1)
		{

			//variables 4.11 & 4.10
			char pattern[] = "\x48\x89\x5C\x24\x00\x48\x89\x6C\x24\x00\x56\x57\x41\x57\x48\x83\xEC\x40\x48\x8B\xF2\x48\x8D\xB9\x00\x00\x00\x00\x45\x33\xFF\x48\x8B\xE9\x48\x8B\xD7\x48\x8B\xCE\x41\x8B\xDF\x45\x8D\x47\x01\xE8\x00\x00\x00\x00\x84\xC0\x0F\x84\x00\x00\x00\x00\x48\x8B\xD6";
			const char* mask = "xxxx?xxxx?xxxxxxxxxxxxxx????xxxxxxxxxxxxxxxxxxxx????xxxx????xxx";


			//Run pattern scan
			pakFileFindAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern), mask);

			if (pakFileFindAddr != -1)
			{
				bNoIsNonPakFileNameAllowed = true;
				return pakFileFindAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}

		//Next Version Scan
		if (pakFileFindAddr == -1)
		{

			//variables 4.9 & 4.8
			char pattern[] = "\x48\x89\x5C\x24\x00\x48\x89\x6C\x24\x00\x56\x57\x41\x57\x48\x83\xEC\x40\x48\x8D\xB9\x00\x00\x00\x00\x48\x8B\xF2\x45\x33\xFF\x48\x8B\xE9\x45\x8D\x47\x01\x48\x8B\xD7\x48\x8B\xCE\x41\x8B\xDF\xE8\x00\x00\x00\x00\x84\xC0\x0F\x84\x00\x00\x00\x00\x48\x8D\x4C\x24\x00\x48\x8B\xD6\x4C\x89\x74\x24\x00\xE8\x00\x00\x00\x00\x39\x5C\x24\x38\x4C\x8D\x35\x00\x00\x00\x00\x49\x8B\xD6\x48\x8B\xCD\x48\x0F\x45\x54\x24\x00\xE8\x00\x00\x00\x00\x48\x8B\xE8\x48\x85\xC0\x0F\x84\x00\x00\x00\x00\x8B\x4F\x08\x85\xC9\x74\x04\xFF\xC9\xEB\x03";
			const char* mask = "xxxx?xxxx?xxxxxxxxxxx????xxxxxxxxxxxxxxxxxxxxxxx????xxxx????xxxx?xxxxxxx?x????xxxxxxx????xxxxxxxxxxx?x????xxxxxxxx????xxxxxxxxxxx";


			//Run pattern scan
			pakFileFindAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern), mask);

			if (pakFileFindAddr != -1)
			{
				bNoIsNonPakFileNameAllowed = true;
				return pakFileFindAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}

		
		//Next Version Scan
		if (pakFileFindAddr == -1)
		{

			//variables 4.7
			char pattern[] = "\x83\xEC\x1C\x53\x8B\x5C\x24\x24\x55\x56\x8B\xE9\x33\xF6\x57\x6A\x01\x8B\xCB\x8D\xBD\x00\x00\x00\x00\x57\xE8\x00\x00\x00\x00\x84\xC0\x0F\x84\x00\x00\x00\x00\x8D\x44\x24\x20\x53\x50\xE8\x00\x00\x00\x00\x83\xC4\x08\xB8\x00\x00\x00\x00\x39\x74\x24\x24\x8B\xCD\x0F\x45\x44\x24\x00\x50\xE8\x00\x00\x00\x00\x89\x44\x24\x30\x85\xC0\x0F\x84\x00\x00\x00\x00\x8B\x4F\x04\x85\xC9\x74\x03\x49\xEB\x02";
			const char* mask = "xxxxxxxxxxxxxxxxxxxxx????xx????xxxx????xxxxxxx????xxxx????xxxxxxxxxx?xx????xxxxxxxx????xxxxxxxxxx";


			//Run pattern scan
			pakFileFindAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern), mask);

			if (pakFileFindAddr != -1)
			{
				bNoIsNonPakFileNameAllowed = true;
				return pakFileFindAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}



		//Exit
		if (pakFileFindAddr == -1)
		{
			return -1;
		}


		return pakFileFindAddr - (uintptr_t)GetModuleHandleW(nullptr);

	}

	//-------------------------------------------------------------------------------------------------------- END





















	//Find IsNonPakFileNameAllowedAddr START
	int Get_IsNonPakFileNameAllowedAddr()
	{

		if (IsNonPakFileNameAllowedAddr == -1)
		{
			//variables 4.22
			char pattern4_22[] = "\x48\x89\x5C\x24\x10\x48\x89\x6C\x24\x18\x56\x57\x41\x56\x48\x83\xEC\x30\x48\x8B\xF9\x45\x33\xC0\x48\x8D\x4C\x24\x20\x4C\x8B\xF2\xE8\x00\x00\x00\x00\x48\x8D\x2D\x00\x00\x00\x00\x83\x78\x08\x00\x74\x05\x48\x8B\x10\xEB\x03";
			const char* mask4_22 = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxx????xxxxxxxxxxx";

			//Run pattern scan 4.22
			IsNonPakFileNameAllowedAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern4_22), mask4_22);

			if (IsNonPakFileNameAllowedAddr != -1)
			{
				return IsNonPakFileNameAllowedAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}


		//Check next version
		if (IsNonPakFileNameAllowedAddr == -1)
		{
			//variables 4.23
			char pattern4_23[] = "\x48\x89\x5C\x24\x10\x48\x89\x6C\x24\x20\x56\x57\x41\x56\x48\x83\xEC\x30\x48\x8B\xD9\x45\x33\xC0\x48\x8D\x4C\x24\x20\x48\x8B\xF2\xE8\x00\x00\x00\x00\x48\x8D\x2D\x00\x00\x00\x00\x83\x78\x08\x00\x74\x05\x48\x8B\x10\xEB\x03";
			const char* mask4_23 = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxx????xxxxxxxxxxx";
			char pattern4_232[] = "";
			//Run pattern scan 4.23
			IsNonPakFileNameAllowedAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern4_23), mask4_23);

			if (IsNonPakFileNameAllowedAddr != -1)
			{
				return IsNonPakFileNameAllowedAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}


		//Check next version
		if (IsNonPakFileNameAllowedAddr == -1)
		{
			//variables 4.24.x
			char pattern4_24[] = "\x48\x89\x5C\x24\x10\x48\x89\x6C\x24\x20\x56\x57\x41\x56\x48\x83\xEC\x30\x48\x8B\xF9\x45\x33\xC0\x48\x8D\x4C\x24\x20\x48\x8B\xF2\xE8\x00\x00\x00\x00\x48\x8D\x2D\x00\x00\x00\x00\x83\x78\x08\x00\x74\x05\x48\x8B\x10\xEB\x03";
			const char* mask4_24 = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxx????xxxxxxxxxxx";

			//Run pattern scan 4.24.x
			IsNonPakFileNameAllowedAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern4_24), mask4_24);

			if (IsNonPakFileNameAllowedAddr != -1)
			{
				return IsNonPakFileNameAllowedAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}

		//Check next version
		if (IsNonPakFileNameAllowedAddr == -1)
		{
			//variables 4.24.3
			char pattern4_24[] = "\x48\x89\x5C\x24\x00\x48\x89\x6C\x24\x00\x56\x57\x41\x56\x48\x83\xEC\x30\x48\x8B\xF9\x45\x33\xC0\x48\x8D\x4C\x24\x00\x48\x8B\xF2\xE8\x00\x00\x00\x00\x48\x8D\x2D\x00\x00\x00\x00\x83\x78\x08\x00\x74\x05\x48\x8B\x10\xEB\x03";
			const char* mask4_24 = "xxxx?xxxx?xxxxxxxxxxxxxxxxxx?xxxx????xxx????xxxxxxxxxxx";

			//Run pattern scan 4.24.3
			IsNonPakFileNameAllowedAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern4_24), mask4_24);

			if (IsNonPakFileNameAllowedAddr != -1)
			{
				return IsNonPakFileNameAllowedAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}


		//Check next version
		if (IsNonPakFileNameAllowedAddr == -1)
		{

			//variables 4.20, 4.21
			char pattern4_21[] = "\x48\x89\x5C\x24\x10\x48\x89\x6C\x24\x18\x48\x89\x74\x24\x20\x57\x48\x83\xEC\x30\x48\x8B\xD9\x45\x33\xC0\x48\x8D\x4C\x24\x20\x48\x8B\xF2\xE8\x00\x00\x00\x00\x48\x8D\x2D\x00\x00\x00\x00\x83\x78\x08\x00\x74\x05\x48\x8B\x10\xEB\x03";
			const char* mask4_21 = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxx????xxxxxxxxxxx";

			//Run pattern scan 4.20, 4.21
			IsNonPakFileNameAllowedAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern4_21), mask4_21);

			if (IsNonPakFileNameAllowedAddr != -1)
			{
				return IsNonPakFileNameAllowedAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}


		//Check next version
		if (IsNonPakFileNameAllowedAddr == -1)
		{

			//variables 4.18
			char pattern4_18[] = "\x48\x89\x5C\x24\x18\x56\x57\x41\x56\x48\x83\xEC\x30\x48\x8B\xD9\x45\x33\xC0\x48\x8D\x4C\x24\x20\x4C\x8B\xF2\xE8\x00\x00\x00\x00\x48\x8D\x35\x00\x00\x00\x00\x83\x78\x08\x00\x74\x05\x48\x8B\x10\xEB\x03";
			const char* mask4_18 = "xxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxx????xxxxxxxxxxx";

			//Run pattern scan 4.18
			IsNonPakFileNameAllowedAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern4_18), mask4_18);

			if (IsNonPakFileNameAllowedAddr != -1)
			{
				return IsNonPakFileNameAllowedAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}


		//Check next version
		if (IsNonPakFileNameAllowedAddr == -1)
		{
			std::cout << "Scanning for IsNonPakFileNameAllowed version 4.18.0 BioMutant type function signature...\n";

			//variables 4.18.0 BioMutant type
			char pattern[] = "\x48\x89\x5C\x24\x00\x48\x89\x74\x24\x00\x41\x56\x48\x83\xEC\x30\x48\x8B\xD9\x45\x33\xC0\x48\x8D\x4C\x24\x00\x4C\x8B\xF2\xE8\x00\x00\x00\x00\x48\x8D\x35\x00\x00\x00\x00\x83\x78\x08\x00\x74\x05\x48\x8B\x10\xEB\x03";
			const char* mask = "xxxx?xxxx?xxxxxxxxxxxxxxxx?xxxx????xxx????xxxxxxxxxxx";

			//Run pattern scan 4.18.0 BioMutant type
			IsNonPakFileNameAllowedAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern), mask);

			if (IsNonPakFileNameAllowedAddr != -1)
			{
				return IsNonPakFileNameAllowedAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}


		//Check next version
		if (IsNonPakFileNameAllowedAddr == -1)
		{

			//variables 4.19
			char pattern4_19[] = "\x48\x89\x5C\x24\x18\x56\x57\x41\x56\x48\x83\xEC\x30\x48\x8B\xD9\x45\x33\xC0\x48\x8D\x4C\x24\x20\x4C\x8B\xF2\xE8\x00\x00\x00\x00\x48\x8D\x35\x00\x00\x00\x00\x83\x78\x08\x00\x74\x05\x48\x8B\x10\xEB\x03";
			const char* mask4_19 = "xxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxx????xxxxxxxxxxx";

			//Run pattern scan 4.19
			IsNonPakFileNameAllowedAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern4_19), mask4_19);

			if (IsNonPakFileNameAllowedAddr != -1)
			{
				return IsNonPakFileNameAllowedAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}


		//Check next version
		if (IsNonPakFileNameAllowedAddr == -1)
		{

			//variables 4.17
			char pattern4_17[] = "\x48\x89\x5C\x24\x18\x56\x57\x41\x56\x48\x83\xEC\x30\x48\x8B\xD9\x45\x33\xC0\x48\x8D\x4C\x24\x20\x4C\x8B\xF2\xE8\x00\x00\x00\x00\x48\x8D\x35\x00\x00\x00\x00\x83\x78\x08\x00\x74\x05\x48\x8B\x10\xEB\x03";
			const char* mask4_17 = "xxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxx????xxxxxxxxxxx";

			//Run pattern scan 4.17
			IsNonPakFileNameAllowedAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern4_17), mask4_17);

			if (IsNonPakFileNameAllowedAddr != -1)
			{
				return IsNonPakFileNameAllowedAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}


		//Check next version
		if (IsNonPakFileNameAllowedAddr == -1)
		{

			//variables 4.16
			char pattern4_16[] = "\x48\x89\x5C\x24\x18\x56\x57\x41\x56\x48\x83\xEC\x30\x48\x8B\xD9\x45\x33\xC0\x48\x8D\x4C\x24\x20\x4C\x8B\xF2\xE8\x00\x00\x00\x00\x48\x8D\x35\x00\x00\x00\x00\x83\x78\x08\x00\x74\x05\x48\x8B\x10\xEB\x03";
			const char* mask4_16 = "xxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxx????xxxxxxxxxxx";

			//Run pattern scan 4.16
			IsNonPakFileNameAllowedAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern4_16), mask4_16);

			if (IsNonPakFileNameAllowedAddr != -1)
			{
				return IsNonPakFileNameAllowedAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}


		//Check next version
		if (IsNonPakFileNameAllowedAddr == -1)
		{

			//variables 4.15
			char pattern4_15[] = "\x48\x89\x5C\x24\x10\x48\x89\x6C\x24\x18\x56\x57\x41\x56\x48\x83\xEC\x30\x48\x8B\xF9\x45\x33\xC0\x48\x8D\x4C\x24\x20\x4C\x8B\xF2\xE8\x00\x00\x00\x00\x48\x8D\x2D\x00\x00\x00\x00\x83\x78\x08\x00\x74\x05\x48\x8B\x10\xEB\x03";
			const char* mask4_15 = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxx????xxxxxxxxxxx";

			//Run pattern scan 4.15
			IsNonPakFileNameAllowedAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern4_15), mask4_15);

			if (IsNonPakFileNameAllowedAddr != -1)
			{
				return IsNonPakFileNameAllowedAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}


		//Check next version
		if (IsNonPakFileNameAllowedAddr == -1)
		{

			//variables 4.14
			char pattern4_14[] = "\x48\x89\x74\x24\x10\x57\x48\x83\xEC\x20\x48\x8B\xF2\xE8\x00\x00\x00\x00\x48\x8B\xF8\x83\x78\x30\x00\x0F\x84\x00\x00\x00\x00\x4C\x8B\x40\x20\x48\x89\x5C\x24\x30\x33\xDB\x4D\x85\xC0\x8B\xC3\x0F\x94\xC0\xF7\xD8\x48\x63\xC8\x48\x23\xCF\x49\x0B\xC8\x74\x4E\x48\x8B\x01\xFF\x50\x38\x84\xC0\x74\x44\x39\x5E\x08\x74\x05\x48\x8B\x16\xEB\x07";
			const char* mask4_14 = "xxxxxxxxxxxxxx????xxxxxxxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";

			//Run pattern scan 4.14
			IsNonPakFileNameAllowedAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern4_14), mask4_14);

			if (IsNonPakFileNameAllowedAddr != -1)
			{
				return IsNonPakFileNameAllowedAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}


		//Check next version
		if (IsNonPakFileNameAllowedAddr == -1)
		{

			//variables 4.25
			char pattern4_25[] = "\x48\x89\x5C\x24\x00\x48\x89\x6C\x24\x00\x56\x57\x41\x56\x48\x83\xEC\x30\x48\x8B\xF1\x45\x33\xC0\x48\x8D\x4C\x24\x00\x4C\x8B\xF2\xE8\x00\x00\x00\x00\x48\x8D\x2D\x00\x00\x00\x00\x83\x78\x08\x00\x74\x05\x48\x8B\x10\xEB\x03";
			const char* mask4_25 = "xxxx?xxxx?xxxxxxxxxxxxxxxxxx?xxxx????xxx????xxxxxxxxxxx";

			//Run pattern scan 4.25
			IsNonPakFileNameAllowedAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern4_25), mask4_25);

			if (IsNonPakFileNameAllowedAddr != -1)
			{
				return IsNonPakFileNameAllowedAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}


		//Check next version
		if (IsNonPakFileNameAllowedAddr == -1)
		{

			//variables 4.25 Kena
			char pattern4_25[] = "\x40\x56\x57\x41\x56\x48\x83\xEC\x40\x48\xC7\x44\x24\x00\x00\x00\x00\x00\x48\x89\x5C\x24\x00\x48\x89\x6C\x24\x00\x4C\x8B\xF2\x48\x8B\xF1\x45\x33\xC0\x48\x8D\x4C\x24\x00\xE8\x00\x00\x00\x00\x90\x48\x8D\x2D\x00\x00\x00\x00\x83\x78\x08\x00\x74\x05\x48\x8B\x10\xEB\x03";
			const char* mask4_25 = "xxxxxxxxxxxxx?????xxxx?xxxx?xxxxxxxxxxxxx?x????xxxx????xxxxxxxxxxx";

			//Run pattern scan 4.25 Kena
			IsNonPakFileNameAllowedAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern4_25), mask4_25);

			if (IsNonPakFileNameAllowedAddr != -1)
			{
				return IsNonPakFileNameAllowedAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}


		//Check next version
		if (IsNonPakFileNameAllowedAddr == -1)
		{

			//variables 4.26
			char pattern4_26[] = "\x48\x89\x5C\x24\x00\x48\x89\x6C\x24\x00\x56\x57\x41\x56\x48\x83\xEC\x30\x48\x8B\xF1\x45\x33\xC0\x48\x8D\x4C\x24\x00\x4C\x8B\xF2\xE8\x00\x00\x00\x00\x48\x8D\x2D\x00\x00\x00\x00\x83\x78\x08\x00\x74\x05\x48\x8B\x10\xEB\x03";
			const char* mask4_26 = "xxxx?xxxx?xxxxxxxxxxxxxxxxxx?xxxx????xxx????xxxxxxxxxxx";

			//Run pattern scan 4.26
			IsNonPakFileNameAllowedAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern4_26), mask4_26);

			if (IsNonPakFileNameAllowedAddr != -1)
			{
				return IsNonPakFileNameAllowedAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}


		//Check next version
		if (IsNonPakFileNameAllowedAddr == -1)
		{

			//variables 4.16 LIS2
			char pattern[] = "\x48\x89\x5C\x24\x00\x56\x57\x41\x56\x48\x83\xEC\x30\x48\x89\xCB\x45\x31\xC0\x48\x8D\x4C\x24\x00\x49\x89\xD6\xE8\x00\x00\x00\x00\x48\x8D\x35\x00\x00\x00\x00\x83\x78\x08\x00\x74\x05\x48\x8B\x10\xEB\x03";
			const char* mask = "xxxx?xxxxxxxxxxxxxxxxxx?xxxx????xxx????xxxxxxxxxxx";

			//Run pattern scan 4.16 LIS2
			IsNonPakFileNameAllowedAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern), mask);

			if (IsNonPakFileNameAllowedAddr != -1)
			{
				return IsNonPakFileNameAllowedAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}


		//Check next version
		if (IsNonPakFileNameAllowedAddr == -1)
		{

			//variables 4.13
			char pattern4_13[] = "\x48\x89\x5C\x24\x00\x48\x89\x74\x24\x00\x48\x89\x7C\x24\x00\x41\x56\x48\x83\xEC\x20\x48\x8B\xF2\x4C\x8B\xF1\xE8\x00\x00\x00\x00\x48\x8B\xF8\x83\x78\x30\x00\x0F\x84\x00\x00\x00\x00\x4C\x8B\x48\x20\x33\xDB\x4D\x85\xC9\x44\x8B\xC3\x41\x0F\x94\xC0\x41\xF7\xD8\x49\x63\xC8\x48\x23\xC8\x49\x0B\xC9\x0F\x84\x00\x00\x00\x00\x48\x8B\x01\xFF\x50\x38\x84\xC0\x74\x7C\x49\x8B\x06\x49\x8B\xCE";
			const char* mask4_13 = "xxxx?xxxx?xxxx?xxxxxxxxxxxxx????xxxxxxxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxxxxxxxxxxxxxx";

			//Run pattern scan 4.13
			IsNonPakFileNameAllowedAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern4_13), mask4_13);

			if (IsNonPakFileNameAllowedAddr != -1)
			{
				return IsNonPakFileNameAllowedAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}


		//Check next version
		if (IsNonPakFileNameAllowedAddr == -1)
		{

			//variables 4.12
			char pattern4_12[] = "\x40\x53\x56\x48\x83\xEC\x58\x80\x79\x51\x00\x48\x8B\xF2\x48\x8B\xD9\x0F\x85\x00\x00\x00\x00\x80\x79\x50\x00\x0F\x84\x00\x00\x00\x00\x83\x7A\x08\x00";
			const char* mask4_12 = "xxxxxxxxxxxxxxxxxxx????xxxxxx????xxxx";

			//Run pattern scan 4.12
			IsNonPakFileNameAllowedAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern4_12), mask4_12);

			if (IsNonPakFileNameAllowedAddr != -1)
			{
				return IsNonPakFileNameAllowedAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}


		//Check next version
		if (IsNonPakFileNameAllowedAddr == -1)
		{

			//variables 4.12 New Retro Arcade
			char pattern4_12_NRA[] = "\x40\x53\x56\x48\x83\xEC\x58\x80\x79\x51\x00\x48\x8B\xF2\x48\x8B\xD9\x0F\x85\x00\x00\x00\x00\x80\x79\x50\x00\x0F\x84\x00\x00\x00\x00\x83\x7A\x08\x00\x48\x89\x7C\x24\x00\x48\x8D\x3D\x00\x00\x00\x00\x4C\x89\x7C\x24\x00\x74\x05\x48\x8B\x12\xEB\x03\x48\x8B\xD7\x41\xB8\x00\x00\x00\x00\x48\x8D\x8C\x24\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x8B\x43\x60\x41\xBF\x00\x00\x00\x00\x3B\x83\x00\x00\x00\x00\x75\x71\x65\x48\x8B\x04\x25\x00\x00\x00\x00\x8B\x15\x00\x00\x00\x00\x4C\x89\x74\x24\x00\x41\x8B\xCF\x4C\x8B\x34\xD0\x4C\x03\xF1\x41\x8B\x06\x39\x05\x00\x00\x00\x00\x0F\x8F\x00\x00\x00\x00";
			const char* mask4_12_NRA = "xxxxxxxxxxxxxxxxxxx????xxxxxx????xxxxxxxx?xxx????xxxx?xxxxxxxxxxxx????xxxx????x????xxxxx????xx????xxxxxxx????xx????xxxx?xxxxxxxxxxxxxxx????xx????";

			//Run pattern scan 4.12
			IsNonPakFileNameAllowedAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern4_12_NRA), mask4_12_NRA);

			if (IsNonPakFileNameAllowedAddr != -1)
			{
				return IsNonPakFileNameAllowedAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}

		//Check next version
		if (IsNonPakFileNameAllowedAddr == -1)
		{

			//variables 4.21 OuterWorlds
			char pattern[] = "\x48\x89\x5C\x24\x00\x48\x89\x6C\x24\x00\x56\x57\x41\x56\x48\x83\xEC\x30\x48\x8B\xF9\x45\x33\xC0\x48\x8D\x4C\x24\x00\x4C\x8B\xF2\xE8\x00\x00\x00\x00\x48\x8D\x2D\x00\x00\x00\x00\x83\x78\x08\x00\x74\x05\x48\x8B\x10\xEB\x03";
			const char* mask = "xxxx?xxxx?xxxxxxxxxxxxxxxxxx?xxxx????xxx????xxxxxxxxxxx";

			//Run pattern scan 4.21
			IsNonPakFileNameAllowedAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern), mask);

			if (IsNonPakFileNameAllowedAddr != -1)
			{
				return IsNonPakFileNameAllowedAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}

		//Check next version
		if (IsNonPakFileNameAllowedAddr == -1)
		{

			//variables 4.27.1
			char pattern[] = "\x48\x89\x5C\x24\x00\x48\x89\x6C\x24\x00\x56\x57\x41\x56\x48\x83\xEC\x30\x48\x8B\xF1\x45\x33\xC0\x48\x8D\x4C\x24\x00\x4C\x8B\xF2\xE8\x00\x00\x00\x00\x48\x8D\x2D\x00\x00\x00\x00\x83\x78\x08\x00\x74\x05\x48\x8B\x10\xEB\x03";
			const char* mask = "xxxx?xxxx?xxxxxxxxxxxxxxxxxx?xxxx????xxx????xxxxxxxxxxx";

			//Run pattern scan 4.27.1
			IsNonPakFileNameAllowedAddr = Util::StartSigScanner(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>(pattern), mask);

			if (IsNonPakFileNameAllowedAddr != -1)
			{
				return IsNonPakFileNameAllowedAddr - (uintptr_t)GetModuleHandleW(nullptr);
			}
		}



		//Exit
		if (IsNonPakFileNameAllowedAddr == -1)
		{
			return -1;
		}

		return IsNonPakFileNameAllowedAddr - (uintptr_t)GetModuleHandleW(nullptr);

	} 
	//-------------------------------------------------------------------------------------------------------- END



} 
//-------------------------------------------------------------------------------------------------------- END OF SigScans NAMESPACE