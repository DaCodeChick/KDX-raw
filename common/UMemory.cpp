#include "UMemory.h"
#include "UError.h"

#include <cstring>

static uint _gAllocationCount = 0;

void UMemory::Clear(void *outDest, uint inSize)
{
	std::memset(outDest, 0, inSize);
}

void UMemory::Dispose(HGLOBAL inPtr)
{
	if (inPtr == NULL)
	{
		return;
	}
	GlobalFree(inPtr);
	_gAllocationCount = _gAllocationCount - 1;
	return;
}

uint UMemory::Move(void *outDest, const void *inSrc, uint inSize)
{
	std::memmove(outDest, inSrc, inSize);
}

TPtr UMemory::New(uint inSize)
{
	HGLOBAL pvVar1;

	if (inSize == 0)
	{
		__Fail(0x10002);
	}
	pvVar1 = GlobalAlloc(0, inSize);
	if (pvVar1 == NULL)
	{
		__Fail(0x20065);
	}
	_gAllocationCount = _gAllocationCount + 1;
	return pvVar1;
}

TPtr UMemory::New(const void *inData, uint inSize)
{
	HGLOBAL pvVar1;

	if (inSize == 0)
	{
		__Fail(0x10002);
	}
	pvVar1 = GlobalAlloc(0, inSize);
	if (pvVar1 == NULL)
	{
		__Fail(0x20065);
	}
	Move(pvVar1, inData, inSize);
	_gAllocationCount = _gAllocationCount + 1;
	return pvVar1;
}

TPtr __cdecl UMemory::NewClear(uint inSize)

{
	HGLOBAL pvVar1;

	if (inSize == 0)
	{
		__Fail(0x10002);
	}
	pvVar1 = GlobalAlloc(GMEM_ZEROINIT, inSize);
	if (pvVar1 == NULL)
	{
		__Fail(0x20065);
	}
	_gAllocationCount = _gAllocationCount + 1;
	return pvVar1;
}

TPtr UMemory::Reallocate(TPtr inPtr, uint inSize)
{
	HGLOBAL pvVar1;

	if (inPtr == NULL)
	{
		pvVar1 = NULL;
		if (inSize != 0)
		{
			pvVar1 = New(inSize);
		}
	}
	else if (inSize == 0)
	{
		Dispose(inPtr);
		pvVar1 = NULL;
	}
	else
	{
		pvVar1 = GlobalReAlloc(inPtr, inSize, 2);
		if (pvVar1 == NULL)
		{
			__Fail(0x20065);
		}
	}
	return pvVar1;
}
