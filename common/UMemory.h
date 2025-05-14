#pragma once

#include "typedefs.h"

#ifdef _WIN32
typedef HGLOBAL TPtr;
#else
typedef void *TPtr;
#endif

class UMemory
{
public:
	static void Clear(void *outDest, uint inSize);
	static void Dispose(TPtr inPtr);
	static uint Move(void *outDest, const void *inSrc, uint inSize);
	static TPtr New(uint inSize);
	static TPtr New(const void *inData, uint inSize);
	static TPtr NewClear(uint inSize);
	static TPtr Reallocate(TPtr inPtr, uint inSize);
};
