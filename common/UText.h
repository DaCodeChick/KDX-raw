#pragma once

#include "typedefs.h"

class EXPORT UText
{
public:
	static bool IsHex(uint inChar);
	static uint ToLower(uint inChar);
	static uint ToUpper(uint inChar);
};
