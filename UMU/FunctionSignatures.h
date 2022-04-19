#pragma once
#include "util.h"
#include "Pattern.h"


class FunctionSignatures
{
public:
	FunctionSignatures();
	int Get_addr_Pakfile__Find();
	int Get_IsNonPakFileNameAllowedAddr();
	~FunctionSignatures();







public:
	//Special Case games that need their own sigs or hooks
	bool bSpecialCaseGame = false;
	bool DQXI_S = false;
	bool bNoIsNonPakFileNameAllowed = false;
	int Find_File_In_PakFile_Version = 1;
	std::string GameName;
	std::string DQXISGame = "DRAGON QUEST XI S";
	std::string DQXISGameDemo = "DRAGON QUEST XI S Demo"; // removed support for this for now.
	uintptr_t pakFileFindAddr = -1;
	uintptr_t IsNonPakFileNameAllowedAddr = -1;

};

