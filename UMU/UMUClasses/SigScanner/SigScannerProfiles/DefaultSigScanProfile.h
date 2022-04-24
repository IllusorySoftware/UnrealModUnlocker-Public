#pragma once
class DefaultSigScanProfile
{
public:
	const unsigned char* p_pattern = nullptr;
	const char* p_mask = nullptr;
	int p_version = 1;
	
public:
	friend class SigScanner_LooseFileLoader;
};

