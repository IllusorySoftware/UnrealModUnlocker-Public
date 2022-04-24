#pragma once
#include "DefaultSigScanProfile.h"

class FindPakSigScanProfile : DefaultSigScanProfile
{
public:
	bool p_bUses_IsNonPakFileNameAllowed = true; //Default to true which means the game has access to IsNonPakFileNameAllowed. 4.0 -> 4.11 = false | 4.12 -> 4.27 = true

public:
	friend class SigScanner_LooseFileLoader;

};

