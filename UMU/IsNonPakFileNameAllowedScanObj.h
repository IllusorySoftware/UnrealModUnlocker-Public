#pragma once
class IsNonPakFileNameAllowedScanObj
{
public:
	const unsigned char* p_pattern = nullptr;
	const char* p_mask = nullptr;

public:
	friend class FunctionSignatures;
};

