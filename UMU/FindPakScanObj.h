#pragma once
class FindPakScanObj
{
public:
	const unsigned char* p_pattern = nullptr;
	const char* p_mask = nullptr;
	int p_Find_File_In_PakFile_Version = 1;
	bool p_bNoIsNonPakFileNameAllowed = false;

public:
	friend class FunctionSignatures;

};

