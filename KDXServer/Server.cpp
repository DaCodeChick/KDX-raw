#include "Server.h"

// KDXServer.exe: 0040c110
void AccountsDBCrypt(void *ioData, uint inDataSize)
{
	uint *puVar1;
	uint uVar2;
	uint uVar3;
	uint uVar4;

	uVar4 = inDataSize >> 2;
	uVar3 = 0;
	uVar2 = 0x9ad22861;
	if (uVar4 != 0)
	{
		if (8 < uVar4)
		{
			uVar2 = 0x9ad22861;
			do
			{
				puVar1 = (uint *)((ulonglong)ioData + uVar3 * 4);
				*puVar1 = *puVar1 ^ ((uVar2 & 0xff00) << 8 | uVar2 >> 0x18 | uVar2 >> 8 & 0xff00 |
				                     uVar2 << 0x18);
				uVar2 = uVar2 * 0x41c64e6d + 0x3039;
				puVar1 = (uint *)((ulonglong)ioData + uVar3 * 4 + 4);
				*puVar1 = *puVar1 ^ ((uVar2 & 0xff00) << 8 | uVar2 >> 0x18 | uVar2 >> 8 & 0xff00 |
				                     uVar2 * 0x1000000);
				uVar2 = uVar2 * 0x41c64e6d + 0x3039;
				puVar1 = (uint *)((ulonglong)ioData + uVar3 * 4 + 8);
				*puVar1 = *puVar1 ^ ((uVar2 & 0xff00) << 8 | uVar2 >> 0x18 | uVar2 >> 8 & 0xff00 |
				                     uVar2 * 0x1000000);
				uVar2 = uVar2 * 0x41c64e6d + 0x3039;
				puVar1 = (uint *)((ulonglong)ioData + uVar3 * 4 + 0xc);
				*puVar1 = *puVar1 ^ ((uVar2 & 0xff00) << 8 | uVar2 >> 0x18 | uVar2 >> 8 & 0xff00 |
				                     uVar2 * 0x1000000);
				uVar2 = uVar2 * 0x41c64e6d + 0x3039;
				puVar1 = (uint *)((ulonglong)ioData + uVar3 * 4 + 0x10);
				*puVar1 = *puVar1 ^ ((uVar2 & 0xff00) << 8 | uVar2 >> 0x18 | uVar2 >> 8 & 0xff00 |
				                     uVar2 * 0x1000000);
				uVar2 = uVar2 * 0x41c64e6d + 0x3039;
				puVar1 = (uint *)((ulonglong)ioData + uVar3 * 4 + 0x14);
				*puVar1 = *puVar1 ^ ((uVar2 & 0xff00) << 8 | uVar2 >> 0x18 | uVar2 >> 8 & 0xff00 |
				                     uVar2 * 0x1000000);
				uVar2 = uVar2 * 0x41c64e6d + 0x3039;
				puVar1 = (uint *)((ulonglong)ioData + uVar3 * 4 + 0x18);
				*puVar1 = *puVar1 ^ ((uVar2 & 0xff00) << 8 | uVar2 >> 0x18 | uVar2 >> 8 & 0xff00 |
				                     uVar2 * 0x1000000);
				uVar2 = uVar2 * 0x41c64e6d + 0x3039;
				puVar1 = (uint *)((ulonglong)ioData + uVar3 * 4 + 0x1c);
				*puVar1 = *puVar1 ^ ((uVar2 & 0xff00) << 8 | uVar2 >> 0x18 | uVar2 >> 8 & 0xff00 |
				                     uVar2 * 0x1000000);
				uVar3 = uVar3 + 8;
				uVar2 = uVar2 * 0x41c64e6d + 0x3039;
			} while (uVar3 < uVar4 - 8);
		}
		for (; uVar3 < uVar4; uVar3 = uVar3 + 1)
		{
			puVar1 = (uint *)((ulonglong)ioData + uVar3 * 4);
			*puVar1 = *puVar1 ^
			          ((uVar2 & 0xff00) << 8 | uVar2 >> 0x18 | uVar2 >> 8 & 0xff00 | uVar2 << 0x18);
			uVar2 = uVar2 * 0x41c64e6d + 0x3039;
		}
	}
	return;
}

// KDXServer.exe: 004177d0
void UDPPacketCrypt(void *outData, const void *inData, uint inDataSize)
{
	uint uVar1;
	uint uVar2;
	uint uVar3;

	uVar1 = inDataSize >> 2;
	uVar3 = 0;
	uVar2 = 0xa5a16c4a;
	if (uVar1 != 0)
	{
		if (8 < uVar1)
		{
			uVar2 = 0xa5a16c4a;
			do
			{
				*(uint *)((ulonglong)outData + uVar3 * 4) =
				    ((uVar2 & 0xff00) << 8 | uVar2 >> 0x18 | uVar2 >> 8 & 0xff00 | uVar2 << 0x18) ^
				    *(uint *)((ulonglong)inData + uVar3 * 4);
				uVar2 = uVar2 * 0x41d28485 + 0x322b;
				*(uint *)((ulonglong)outData + uVar3 * 4 + 4) =
				    ((uVar2 & 0xff00) << 8 | uVar2 >> 0x18 | uVar2 >> 8 & 0xff00 |
				     uVar2 * 0x1000000) ^
				    *(uint *)((ulonglong)inData + uVar3 * 4 + 4);
				uVar2 = uVar2 * 0x41d28485 + 0x322b;
				*(uint *)((ulonglong)outData + uVar3 * 4 + 8) =
				    ((uVar2 & 0xff00) << 8 | uVar2 >> 0x18 | uVar2 >> 8 & 0xff00 |
				     uVar2 * 0x1000000) ^
				    *(uint *)((ulonglong)inData + uVar3 * 4 + 8);
				uVar2 = uVar2 * 0x41d28485 + 0x322b;
				*(uint *)((ulonglong)outData + uVar3 * 4 + 0xc) =
				    ((uVar2 & 0xff00) << 8 | uVar2 >> 0x18 | uVar2 >> 8 & 0xff00 |
				     uVar2 * 0x1000000) ^
				    *(uint *)((ulonglong)inData + uVar3 * 4 + 0xc);
				uVar2 = uVar2 * 0x41d28485 + 0x322b;
				*(uint *)((ulonglong)outData + uVar3 * 4 + 0x10) =
				    ((uVar2 & 0xff00) << 8 | uVar2 >> 0x18 | uVar2 >> 8 & 0xff00 |
				     uVar2 * 0x1000000) ^
				    *(uint *)((ulonglong)inData + uVar3 * 4 + 0x10);
				uVar2 = uVar2 * 0x41d28485 + 0x322b;
				*(uint *)((ulonglong)outData + uVar3 * 4 + 0x14) =
				    ((uVar2 & 0xff00) << 8 | uVar2 >> 0x18 | uVar2 >> 8 & 0xff00 |
				     uVar2 * 0x1000000) ^
				    *(uint *)((ulonglong)inData + uVar3 * 4 + 0x14);
				uVar2 = uVar2 * 0x41d28485 + 0x322b;
				*(uint *)((ulonglong)outData + uVar3 * 4 + 0x18) =
				    ((uVar2 & 0xff00) << 8 | uVar2 >> 0x18 | uVar2 >> 8 & 0xff00 |
				     uVar2 * 0x1000000) ^
				    *(uint *)((ulonglong)inData + uVar3 * 4 + 0x18);
				uVar2 = uVar2 * 0x41d28485 + 0x322b;
				*(uint *)((ulonglong)outData + uVar3 * 4 + 0x1c) =
				    ((uVar2 & 0xff00) << 8 | uVar2 >> 0x18 | uVar2 >> 8 & 0xff00 |
				     uVar2 * 0x1000000) ^
				    *(uint *)((ulonglong)inData + uVar3 * 4 + 0x1c);
				uVar3 = uVar3 + 8;
				uVar2 = uVar2 * 0x41d28485 + 0x322b;
			} while (uVar3 < uVar1 - 8);
		}
		for (; uVar3 < uVar1; uVar3 = uVar3 + 1)
		{
			*(uint *)((ulonglong)outData + uVar3 * 4) =
			    ((uVar2 & 0xff00) << 8 | uVar2 >> 0x18 | uVar2 >> 8 & 0xff00 | uVar2 << 0x18) ^
			    *(uint *)((ulonglong)inData + uVar3 * 4);
			uVar2 = uVar2 * 0x41d28485 + 0x322b;
		}
	}
	return;
}
