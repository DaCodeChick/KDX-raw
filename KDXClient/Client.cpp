#include "Client.h"

// KDXClient.exe: 00473340
void UDPPacketCrypt(void *outData, const void *inData, uint inDataSize)
{
	uint uVar1;
	uint uVar2;
	uint uVar3;

	uVar1 = inDataSize >> 2;
	uVar3 = 0;
	uVar2 = 0xe4fdbaa9;
	if (uVar1 != 0)
	{
		if (8 < uVar1)
		{
			uVar2 = 0xe4fdbaa9;
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
