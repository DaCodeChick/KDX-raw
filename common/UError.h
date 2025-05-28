#pragma once

#include "typedefs.h"

struct SError
{
	uint id; /// Unique identifier for the error
	uint field1_0x4;
	uint field2_0x8;
	uint field3_0xc;
	uint field4_0x10;
};

/**
 * @brief Fails the current operation with the given error ID.
 * 
 * @param inID Unique identifier for the error to be raised.
 */
EXPORT void __Fail(uint inID);
