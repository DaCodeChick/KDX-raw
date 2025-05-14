#pragma once

#include "typedefs.h"

class UText
{
public:
	static bool Equal(const char *inTextA, const char *inTextB, uint inSize);
	static bool IsHex(uint inChar);
	static uint ToLower(uint inChar);
	static uint ToUpper(uint inChar);
};
