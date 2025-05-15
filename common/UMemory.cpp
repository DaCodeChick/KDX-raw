#include "UMemory.h"
#include "UError.h"

#ifndef _WIN32
#include <cstring>
#endif

// AppearanceEdit.app: 1009011c
// AppearanceEdit.exe: 004602fc
// KDXClient.exe: 004fed7c
// KDXClient.lexe: 081a0c40
// KDXServer.app: 1009d3ac
// KDXServer.command: 000e4edc
static uint _gAllocationCount = 0;

// AppearanceEdit.app: 1004c390
// AppearanceEdit.exe: 004245a0
// KDXClient.exe: 0046baf0
// KDXClient.lexe: 080c7fbc
// KDXServer.app: 1005eb50
// KDXServer.command: 0003409c
void UMemory::Clear(void *outDest, uint inSize)
{
	uint uVar1;
	uint uVar2;

	while (true)
	{
		while (true)
		{
			while (true)
			{
				while (true)
				{
					while (true)
					{
						uVar2 = inSize;
						if (((ulonglong)outDest & 0x1f) == 0)
						{
							uVar2 = inSize & 0x3f;
							for (uVar1 = inSize >> 6; uVar1 != 0; uVar1 = uVar1 - 1)
							{
								*(undefined8 *)outDest = 0;
								*(undefined8 *)((ulonglong)outDest + 8) = 0;
								*(undefined8 *)((ulonglong)outDest + 0x10) = 0;
								*(undefined8 *)((ulonglong)outDest + 0x18) = 0;
								*(undefined8 *)((ulonglong)outDest + 0x20) = 0;
								*(undefined8 *)((ulonglong)outDest + 0x28) = 0;
								*(undefined8 *)((ulonglong)outDest + 0x30) = 0;
								*(undefined8 *)((ulonglong)outDest + 0x38) = 0;
								outDest = (void *)((ulonglong)outDest + 0x40);
							}
							if (0x1f < uVar2)
							{
								*(undefined8 *)outDest = 0;
								*(undefined8 *)((ulonglong)outDest + 8) = 0;
								*(undefined8 *)((ulonglong)outDest + 0x10) = 0;
								*(undefined8 *)((ulonglong)outDest + 0x18) = 0;
								outDest = (void *)((ulonglong)outDest + 0x20);
								uVar2 = uVar2 - 0x20;
							}
						}
						if ((((ulonglong)outDest & 0xf) != 0) || (uVar2 < 0x10))
							break;
						*(undefined8 *)outDest = 0;
						*(undefined8 *)((ulonglong)outDest + 8) = 0;
						outDest = (void *)((ulonglong)outDest + 0x10);
						inSize = uVar2 - 0x10;
					}
					if ((((ulonglong)outDest & 7) != 0) || (uVar2 < 8))
						break;
					*(undefined8 *)outDest = 0;
					outDest = (void *)((ulonglong)outDest + 8);
					inSize = uVar2 - 8;
				}
				if ((((ulonglong)outDest & 3) != 0) || (uVar2 < 4))
					break;
				*(undefined4 *)outDest = 0;
				outDest = (void *)((ulonglong)outDest + 4);
				inSize = uVar2 - 4;
			}
			if ((((ulonglong)outDest & 1) != 0) || (uVar2 < 2))
				break;
			*(undefined2 *)outDest = 0;
			outDest = (void *)((ulonglong)outDest + 2);
			inSize = uVar2 - 2;
		}
		if (uVar2 == 0)
			break;
		*(undefined1 *)outDest = 0;
		outDest = (void *)((ulonglong)outDest + 1);
		inSize = uVar2 - 1;
	}
	return;
}

// AppearanceEdit.app: 1004c120
// AppearanceEdit.exe: 00415080
// KDXClient.exe: 004577d0
// KDXClient.lexe: 08108cc0
// KDXServer.app: 1005e7c0
// KDXServer.command: 000176c8
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

// AppearanceEdit.app: 1004c3c0
// AppearanceEdit.exe: 00414f20
// KDXClient.exe: 0047b740
// KDXClient.lexe: 080c7930
// KDXServer.app: 1005eb80
// KDXServer.command: 00033868
uint UMemory::Move(void *outDest, const void *inSrc, uint inSize)
{
#ifdef _WIN32
	uint uVar1;
	uint uVar2;
	undefined4 *puVar3;
	undefined1 *puVar4;
	undefined4 *puVar5;
	undefined1 *puVar6;

	if (inSrc < outDest)
	{
		puVar4 = (undefined1 *)((ulonglong)inSrc + (inSize - 1));
		puVar6 = (undefined1 *)((ulonglong)outDest + (inSize - 1));
		uVar2 = inSize;
		if (0xf < (int)inSize)
		{
			uVar2 = (ulonglong)(puVar6 + -3) & 3;
			uVar1 = inSize;
			if (uVar2 != 0)
			{
				uVar1 = inSize - uVar2;
				for (; uVar2 != 0; uVar2 = uVar2 - 1)
				{
					*puVar6 = *puVar4;
					puVar4 = puVar4 + -1;
					puVar6 = puVar6 + -1;
				}
			}
			uVar2 = uVar1 & 7;
			puVar3 = (undefined4 *)(puVar4 + -3);
			puVar5 = (undefined4 *)(puVar6 + -3);
			for (uVar1 = uVar1 >> 2; uVar1 != 0; uVar1 = uVar1 - 1)
			{
				*puVar5 = *puVar3;
				puVar3 = puVar3 + -1;
				puVar5 = puVar5 + -1;
			}
			if (uVar2 == 0)
			{
				return inSize;
			}
			puVar4 = (undefined1 *)((ulonglong)puVar3 + 3);
			puVar6 = (undefined1 *)((ulonglong)puVar5 + 3);
		}
		for (; uVar2 != 0; uVar2 = uVar2 - 1)
		{
			*puVar6 = *puVar4;
			puVar4 = puVar4 + -1;
			puVar6 = puVar6 + -1;
		}
	}
	else
	{
		uVar2 = inSize;
		if (0xf < (int)inSize)
		{
			uVar2 = -(ulonglong)outDest & 7;
			uVar1 = inSize;
			if (uVar2 != 0)
			{
				uVar1 = inSize - uVar2;
				for (; uVar2 != 0; uVar2 = uVar2 - 1)
				{
					*(undefined1 *)outDest = *(byte *)inSrc;
					inSrc = (undefined4 *)((ulonglong)inSrc + 1);
					outDest = (undefined4 *)((ulonglong)outDest + 1);
				}
			}
			uVar2 = uVar1 & 7;
			for (uVar1 = uVar1 >> 2; uVar1 != 0; uVar1 = uVar1 - 1)
			{
				*(undefined4 *)outDest = *(byte *)inSrc;
				inSrc = (undefined4 *)((ulonglong)inSrc + 4);
				outDest = (undefined4 *)((ulonglong)outDest + 4);
			}
			if (uVar2 == 0)
			{
				return inSize;
			}
		}
		for (; uVar2 != 0; uVar2 = uVar2 - 1)
		{
			*(undefined1 *)outDest = *(byte *)inSrc;
			inSrc = (undefined4 *)((ulonglong)inSrc + 1);
			outDest = (undefined4 *)((ulonglong)outDest + 1);
		}
	}
	return inSize;
#else
	std::memmove(outDest, inSrc, inSize);
#endif
	return inSize;
}

// AppearanceEdit.app: 1004bf80
// AppearanceEdit.exe: 00414fb0
// KDXClient.exe: 00457700
// KDXClient.lexe: 08108ba0
// KDXServer.app: 1005e650
// KDXServer.command: 0001754c
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

// AppearanceEdit.exe: 00414ff0
// KDXClient.exe: 00457740
// KDXClient.lexe: 08108bf8
// KDXServer.app: 1005e6c0
// KDXServer.command: 000175c0
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

// AppearanceEdit.app: 1004c0a0
// AppearanceEdit.exe: 00415040
// KDXClient.exe: 00457790
// KDXClient.lexe: 08108c5c
// KDXServer.app: 1005e750
// KDXServer.command: 00017648
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

// AppearanceEdit.exe: 004150b0
// KDXClient.exe: 00457800
// KDXClient.lexe: 08108cec
// KDXServer.command: 00017724
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
