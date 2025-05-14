#include "UError.h"

void __Fail(uint inID)
{
	SError err;
	err.id = inID;
	err.field1_0x4 = 0;
	err.field2_0x8 = 0;
	err.field3_0xc = 0;
	err.field4_0x10 = 0;
	throw err;
}