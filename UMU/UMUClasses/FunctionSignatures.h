#pragma once
#include "../Tools/util.h"
#include "FindPakScanObj.h"
#include "IsNonPakFileNameAllowedScanObj.h"
#include <vector>


class FunctionSignatures
{
public:
	FunctionSignatures();
	void init();
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

public:
	FindPakScanObj PakScanObj_1;
	FindPakScanObj PakScanObj_2;
	FindPakScanObj PakScanObj_3;
	FindPakScanObj PakScanObj_4;
	FindPakScanObj PakScanObj_5;
	FindPakScanObj PakScanObj_6;
	FindPakScanObj PakScanObj_7;
	FindPakScanObj PakScanObj_8;
	FindPakScanObj PakScanObj_9;
	FindPakScanObj PakScanObj_10;
	FindPakScanObj PakScanObj_11;
	FindPakScanObj PakScanObj_12;
	FindPakScanObj PakScanObj_13;
	FindPakScanObj PakScanObj_14;
	FindPakScanObj PakScanObj_15;
	FindPakScanObj PakScanObj_16;
	FindPakScanObj PakScanObj_17;
	FindPakScanObj PakScanObj_18;
	FindPakScanObj PakScanObj_19;
	FindPakScanObj PakScanObj_20;
	std::vector<FindPakScanObj> FindPakScanVector;

public:
	IsNonPakFileNameAllowedScanObj IsNonPakFileNameAllowedScanObj_1;
	IsNonPakFileNameAllowedScanObj IsNonPakFileNameAllowedScanObj_2;
	IsNonPakFileNameAllowedScanObj IsNonPakFileNameAllowedScanObj_3;
	IsNonPakFileNameAllowedScanObj IsNonPakFileNameAllowedScanObj_4;
	IsNonPakFileNameAllowedScanObj IsNonPakFileNameAllowedScanObj_5;
	IsNonPakFileNameAllowedScanObj IsNonPakFileNameAllowedScanObj_6;
	IsNonPakFileNameAllowedScanObj IsNonPakFileNameAllowedScanObj_7;
	IsNonPakFileNameAllowedScanObj IsNonPakFileNameAllowedScanObj_8;
	IsNonPakFileNameAllowedScanObj IsNonPakFileNameAllowedScanObj_9;
	IsNonPakFileNameAllowedScanObj IsNonPakFileNameAllowedScanObj_10;
	IsNonPakFileNameAllowedScanObj IsNonPakFileNameAllowedScanObj_11;
	IsNonPakFileNameAllowedScanObj IsNonPakFileNameAllowedScanObj_12;
	IsNonPakFileNameAllowedScanObj IsNonPakFileNameAllowedScanObj_13;
	IsNonPakFileNameAllowedScanObj IsNonPakFileNameAllowedScanObj_14;
	IsNonPakFileNameAllowedScanObj IsNonPakFileNameAllowedScanObj_15;
	IsNonPakFileNameAllowedScanObj IsNonPakFileNameAllowedScanObj_16;
	IsNonPakFileNameAllowedScanObj IsNonPakFileNameAllowedScanObj_17;
	IsNonPakFileNameAllowedScanObj IsNonPakFileNameAllowedScanObj_18;
	IsNonPakFileNameAllowedScanObj IsNonPakFileNameAllowedScanObj_19;
	IsNonPakFileNameAllowedScanObj IsNonPakFileNameAllowedScanObj_20;
	std::vector<IsNonPakFileNameAllowedScanObj> IsNonPakFileNameAllowedScanVector;

public:
	friend class FindPakScanObj;
	friend class IsNonPakFileNameAllowedScanObj;

};

