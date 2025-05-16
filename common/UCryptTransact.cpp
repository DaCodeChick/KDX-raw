#include "UCryptTransact.h"
#include "UDigest.h"
#include "UMemory.h"

// KDXServer.exe: 00417a30
void UCryptTransact::BlockCrypt6E7DFD34(void *ioData, bool inIsDecrypt)
{
	uint uVar1;
	uint uVar2;
	uint uVar3;
	uint uVar4;
	uint uVar5;
	uint uVar6;
	uint uVar7;
	uint uVar8;

	uVar8 = *(uint *)ioData;
	uVar1 = *(uint *)((ulonglong)ioData + 4);
	uVar6 = (uVar8 & 0xff00) << 8 | uVar8 >> 0x18 | uVar8 >> 8 & 0xff00 | uVar8 << 0x18;
	uVar7 = *(uint *)((ulonglong)ioData + 8);
	uVar3 = (uVar1 & 0xff00) << 8 | uVar1 >> 0x18 | uVar1 >> 8 & 0xff00;
	uVar4 = uVar3 | uVar1 << 0x18;
	uVar1 = *(uint *)((ulonglong)ioData + 0xc);
	uVar2 = (uVar7 & 0xff00) << 8 | uVar7 >> 0x18 | uVar7 >> 8 & 0xff00 | uVar7 << 0x18;
	uVar5 = (uVar1 & 0xff00) << 8 | uVar1 >> 0x18 | uVar1 >> 8 & 0xff00 | uVar1 << 0x18;
	if (inIsDecrypt)
	{
		uVar3 = (uVar3 << 0xd | uVar4 >> 0x13) ^ 0x6e7dfd34;
		uVar7 = (uVar2 >> 6 | (uVar7 >> 0x18) << 0x1a) ^ 0xe152da04;
		*(uint *)ioData =
		    (uVar3 & 0xff00) << 8 | uVar3 >> 0x18 | uVar3 >> 8 & 0xff00 | uVar3 << 0x18;
		*(uint *)((ulonglong)ioData + 4) =
		    (uVar7 & 0xff00) << 8 | uVar7 >> 0x18 | uVar7 >> 8 & 0xff00 | uVar7 << 0x18;
		uVar8 = ((uVar8 << 0x18) >> 0x19 | uVar6 << 7) ^ 0xa95a759b;
		*(uint *)((ulonglong)ioData + 8) =
		    (uVar8 & 0xff00) << 8 | uVar8 >> 0x18 | uVar8 >> 8 & 0xff00 | uVar8 << 0x18;
		uVar8 = ((uVar1 >> 0x18) << 0x1d | uVar5 >> 3) ^ 0x6992e25;
		*(uint *)((ulonglong)ioData + 0xc) =
		    (uVar8 & 0xff00) << 8 | uVar8 >> 0x18 | uVar8 >> 8 & 0xff00 | uVar8 << 0x18;
	}
	else
	{
		uVar2 = uVar2 ^ 0xa95a759b;
		uVar8 = uVar2 >> 7;
		uVar6 = uVar6 ^ 0x6e7dfd34;
		uVar3 = uVar6 << 0x13;
		uVar6 = uVar6 >> 0xd;
		*(uint *)ioData = (uVar8 & 0xff00) << 8 | (uVar2 << 0x19 | uVar8) >> 0x18 |
		                  (uVar8 & 0xff0000) >> 8 | uVar8 << 0x18;
		uVar4 = uVar4 ^ 0xe152da04;
		uVar7 = uVar4 << 6;
		uVar8 = (uVar5 ^ 0x6992e25) * 8;
		*(uint *)((ulonglong)ioData + 4) =
		    (uVar6 & 0xff00) << 8 | uVar3 >> 0x18 | (uVar6 | uVar3) >> 8 & 0xff00 | uVar6 << 0x18;
		*(uint *)((ulonglong)ioData + 8) = (uVar7 & 0xff00) << 8 | uVar7 >> 0x18 |
		                                   uVar7 >> 8 & 0xff00 | (uVar7 | uVar4 >> 0x1a) << 0x18;
		*(uint *)((ulonglong)ioData + 0xc) = (uVar8 & 0xff00) << 8 | uVar8 >> 0x18 |
		                                     uVar8 >> 8 & 0xff00 |
		                                     ((uVar1 << 0x18) >> 0x1d | uVar8) << 0x18;
	}
	return;
}

// KDXServer.exe: 00442070
void UCryptTransact::GenerateKey(const void *inData, uint inDataSize, void *outData)
{
	uint uVar1;
	_MD5 local_90;

	if (inDataSize == 0)
	{
		*(undefined4 *)outData = 0xeea339da;
		*(undefined4 *)((ulonglong)outData + 4) = 0x6ebeaeca;
		*(undefined4 *)((ulonglong)outData + 8) = 0xd4b6b5e;
		*(undefined4 *)((ulonglong)outData + 0xc) = 0xba298eba;
		*(undefined4 *)((ulonglong)outData + 0x10) = 0xefbf5532;
		*(undefined4 *)((ulonglong)outData + 0x14) = 0xc4b5a218;
		*(undefined4 *)((ulonglong)outData + 0x18) = 0x90186095;
		*(undefined4 *)((ulonglong)outData + 0x1c) = 0x907d8af;
		return;
	}
	local_90.Init();
	local_90.Update(inData, inDataSize);
	local_90.Report(outData);
	*(undefined4 *)((ulonglong)outData + 0x14) = *(uint *)outData;
	*(undefined4 *)((ulonglong)outData + 0x18) = *(undefined4 *)((ulonglong)outData + 4);
	uVar1 = UMemory::Checksum(inData, inDataSize, 1);
	*(uint *)((ulonglong)outData + 0x1c) =
	    (uVar1 & 0xff00) << 8 | uVar1 >> 0x18 | uVar1 >> 8 & 0xff00 | uVar1 << 0x18;
	return;
}

// KDXServer.exe: 00442140
bool UCryptTransact::IsDefaultKey(const void *inData)
{
	bool bVar1;
	undefined1 local_24[32];

	GenerateKey(0, 0, local_24);
	bVar1 = UMemory::Compare(local_24, inData, 0x20);
	return bVar1;
}

// KDXServer.exe: 00430b40
void UCryptTransact::TCPPacketCrypt(uint inInit, void *ioData, uint inDataSize)
{
	uint *puVar1;
	uint uVar2;
	uint uVar3;
	uint uVar4;

	uVar4 = inDataSize >> 2;
	uVar3 = 0;
	if (uVar4 != 0)
	{
		if (8 < uVar4)
		{
			do
			{
				uVar2 = inInit * 2 + 0x4878;
				puVar1 = (uint *)((ulonglong)ioData + uVar3 * 4);
				*puVar1 = *puVar1 ^ ((uVar2 & 0xff00) << 8 | uVar2 >> 0x18 | uVar2 >> 8 & 0xff00 |
				                     uVar2 * 0x1000000);
				uVar2 = uVar2 * 2 + 0x4878;
				puVar1 = (uint *)((ulonglong)ioData + uVar3 * 4 + 4);
				*puVar1 = *puVar1 ^ ((uVar2 & 0xff00) << 8 | uVar2 >> 0x18 | uVar2 >> 8 & 0xff00 |
				                     uVar2 * 0x1000000);
				uVar2 = uVar2 * 2 + 0x4878;
				puVar1 = (uint *)((ulonglong)ioData + uVar3 * 4 + 8);
				*puVar1 = *puVar1 ^ ((uVar2 & 0xff00) << 8 | uVar2 >> 0x18 | uVar2 >> 8 & 0xff00 |
				                     uVar2 * 0x1000000);
				uVar2 = uVar2 * 2 + 0x4878;
				puVar1 = (uint *)((ulonglong)ioData + uVar3 * 4 + 0xc);
				*puVar1 = *puVar1 ^ ((uVar2 & 0xff00) << 8 | uVar2 >> 0x18 | uVar2 >> 8 & 0xff00 |
				                     uVar2 * 0x1000000);
				uVar2 = uVar2 * 2 + 0x4878;
				puVar1 = (uint *)((ulonglong)ioData + uVar3 * 4 + 0x10);
				*puVar1 = *puVar1 ^ ((uVar2 & 0xff00) << 8 | uVar2 >> 0x18 | uVar2 >> 8 & 0xff00 |
				                     uVar2 * 0x1000000);
				uVar2 = uVar2 * 2 + 0x4878;
				puVar1 = (uint *)((ulonglong)ioData + uVar3 * 4 + 0x14);
				*puVar1 = *puVar1 ^ ((uVar2 & 0xff00) << 8 | uVar2 >> 0x18 | uVar2 >> 8 & 0xff00 |
				                     uVar2 * 0x1000000);
				uVar2 = uVar2 * 2 + 0x4878;
				puVar1 = (uint *)((ulonglong)ioData + uVar3 * 4 + 0x18);
				*puVar1 = *puVar1 ^ ((uVar2 & 0xff00) << 8 | uVar2 >> 0x18 | uVar2 >> 8 & 0xff00 |
				                     uVar2 * 0x1000000);
				inInit = uVar2 * 2 + 0x4878;
				puVar1 = (uint *)((ulonglong)ioData + uVar3 * 4 + 0x1c);
				*puVar1 = *puVar1 ^ ((inInit & 0xff00) << 8 | inInit >> 0x18 |
				                     inInit >> 8 & 0xff00 | inInit * 0x1000000);
				uVar3 = uVar3 + 8;
			} while (uVar3 < uVar4 - 8);
		}
		for (; uVar3 < uVar4; uVar3 = uVar3 + 1)
		{
			inInit = inInit * 2 + 0x4878;
			puVar1 = (uint *)((ulonglong)ioData + uVar3 * 4);
			*puVar1 = *puVar1 ^ ((inInit & 0xff00) << 8 | inInit >> 0x18 | inInit >> 8 & 0xff00 |
			                     inInit * 0x1000000);
		}
	}
	return;
}
