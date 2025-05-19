#include "Client.h"

// KDXClient.exe: 0046cdb0
void BlockCrypt1B20E200(void *ioData, bool inIsDecrypt)
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
	uVar6 = *(uint *)((ulonglong)ioData + 4);
	uVar5 = (uVar8 & 0xff00) << 8 | uVar8 >> 0x18 | uVar8 >> 8 & 0xff00 | uVar8 << 0x18;
	uVar1 = *(uint *)((ulonglong)ioData + 8);
	uVar2 = (uVar6 & 0xff00) << 8 | uVar6 >> 0x18 | uVar6 >> 8 & 0xff00;
	uVar3 = uVar2 | uVar6 << 0x18;
	uVar7 = uVar1 >> 0x18;
	uVar6 = *(uint *)((ulonglong)ioData + 0xc);
	uVar1 = (uVar1 & 0xff00) << 8 | uVar7 | uVar1 >> 8 & 0xff00 | uVar1 << 0x18;
	uVar4 = (uVar6 & 0xff00) << 8 | uVar6 >> 0x18 | uVar6 >> 8 & 0xff00 | uVar6 << 0x18;
	if (inIsDecrypt)
	{
		uVar2 = (uVar3 >> 0x11 | uVar2 << 0xf) ^ 0x5f547a17;
		uVar1 = (uVar1 >> 4 | uVar7 << 0x1c) ^ 0x69c83e35;
		*(uint *)ioData =
		    (uVar2 & 0xff00) << 8 | uVar2 >> 0x18 | uVar2 >> 8 & 0xff00 | uVar2 << 0x18;
		*(uint *)((ulonglong)ioData + 4) =
		    (uVar1 & 0xff00) << 8 | uVar1 >> 0x18 | uVar1 >> 8 & 0xff00 | uVar1 << 0x18;
		uVar8 = (uVar8 << 0x18) >> 0x19 | uVar5 << 7;
		uVar1 = uVar8 ^ 0x1b20e200;
		*(uint *)((ulonglong)ioData + 8) =
		    (uVar1 & 0xff00) << 8 | uVar1 >> 0x18 | uVar1 >> 8 & 0xff00 | uVar8 << 0x18;
		uVar8 = ((uVar6 >> 0x18) << 0x1b | uVar4 >> 5) ^ 0x8022e8d1;
		*(uint *)((ulonglong)ioData + 0xc) =
		    (uVar8 & 0xff00) << 8 | uVar8 >> 0x18 | uVar8 >> 8 & 0xff00 | uVar8 << 0x18;
	}
	else
	{
		uVar8 = (uVar1 ^ 0x1b20e200) >> 7;
		uVar5 = uVar5 ^ 0x5f547a17;
		uVar1 = uVar5 >> 0xf;
		uVar5 = uVar5 << 0x11;
		*(uint *)ioData = (uVar8 & 0xff00) << 8 | (uVar7 << 0x19 | uVar8) >> 0x18 |
		                  (uVar8 & 0xff0000) >> 8 | uVar8 << 0x18;
		uVar3 = uVar3 ^ 0x69c83e35;
		uVar8 = uVar3 << 4;
		uVar4 = uVar4 ^ 0x8022e8d1;
		uVar6 = uVar4 << 5;
		*(uint *)((ulonglong)ioData + 4) =
		    (uVar1 & 0xff00) << 8 | uVar5 >> 0x18 | (uVar5 | uVar1) >> 8 & 0xff00 | uVar1 << 0x18;
		*(uint *)((ulonglong)ioData + 8) = (uVar8 & 0xff00) << 8 | uVar8 >> 0x18 |
		                                   uVar8 >> 8 & 0xff00 | (uVar8 | uVar3 >> 0x1c) << 0x18;
		*(uint *)((ulonglong)ioData + 0xc) = (uVar6 & 0xff00) << 8 | uVar6 >> 0x18 |
		                                     uVar6 >> 8 & 0xff00 | (uVar4 >> 0x1b | uVar6) << 0x18;
	}
	return;
}

// KDXClient.exe: 00472310
void CertificateCrypt(const void *inData, void *outData)
{
	uint uVar1;
	uint uVar2;
	uint uVar3;
	uint uVar4;

	uVar1 = (uint) * (byte *)inData;
	*(byte *)outData = *(byte *)inData;
	uVar3 = 0x7be0023;
	uVar2 = 1;
	if (uVar1 != 0)
	{
		if (8 < uVar1)
		{
			do
			{
				*(byte *)((ulonglong)outData + uVar2) =
				    (byte)uVar3 ^ *(byte *)((ulonglong)inData + uVar2);
				uVar3 = (uVar3 ^ uVar2) + 0x23cca7;
				*(byte *)((ulonglong)outData + uVar2 + 1) =
				    (byte)uVar3 ^ *(byte *)((ulonglong)inData + uVar2 + 1);
				uVar3 = (uVar3 ^ uVar2 + 1) + 0x23cca7;
				*(byte *)((ulonglong)outData + uVar2 + 2) =
				    (byte)uVar3 ^ *(byte *)((ulonglong)inData + uVar2 + 2);
				uVar3 = (uVar3 ^ uVar2 + 2) + 0x23cca7;
				*(byte *)((ulonglong)outData + uVar2 + 3) =
				    (byte)uVar3 ^ *(byte *)((ulonglong)inData + uVar2 + 3);
				uVar3 = (uVar3 ^ uVar2 + 3) + 0x23cca7;
				*(byte *)((ulonglong)outData + uVar2 + 4) =
				    (byte)uVar3 ^ *(byte *)((ulonglong)inData + uVar2 + 4);
				uVar3 = (uVar3 ^ uVar2 + 4) + 0x23cca7;
				*(byte *)((ulonglong)outData + uVar2 + 5) =
				    (byte)uVar3 ^ *(byte *)((ulonglong)inData + uVar2 + 5);
				uVar3 = (uVar3 ^ uVar2 + 5) + 0x23cca7;
				*(byte *)((ulonglong)outData + uVar2 + 6) =
				    (byte)uVar3 ^ *(byte *)((ulonglong)inData + uVar2 + 6);
				uVar4 = (uVar3 ^ uVar2 + 6) + 0x23cca7;
				uVar3 = uVar2 + 7;
				*(byte *)((ulonglong)outData + uVar2 + 7) =
				    (byte)uVar4 ^ *(byte *)((ulonglong)inData + uVar2 + 7);
				uVar2 = uVar2 + 8;
				uVar3 = (uVar4 ^ uVar3) + 0x23cca7;
			} while (uVar2 <= uVar1 - 8);
		}
		for (; uVar2 <= uVar1; uVar2 = uVar2 + 1)
		{
			*(byte *)((ulonglong)outData + uVar2) =
			    (byte)uVar3 ^ *(byte *)((ulonglong)inData + uVar2);
			uVar3 = (uVar3 ^ uVar2) + 0x23cca7;
		}
	}
	return;
}

// KDXClient.exe: 00473340
void CryptE4FDBAA9(void *outData, const void *inData, uint inDataSize)
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

// KDXClient.exe: 00410060
void SettingsCrypt(void *ioData, uint inDataSize)
{
	uint *puVar1;
	uint uVar2;
	uint uVar3;
	uint uVar4;

	uVar4 = inDataSize >> 2;
	uVar3 = 0;
	uVar2 = 0x35662cb6;
	if (uVar4 != 0)
	{
		if (8 < uVar4)
		{
			uVar2 = 0x35662cb6;
			do
			{
				puVar1 = (uint *)((ulonglong)ioData + uVar3 * 4);
				*puVar1 = *puVar1 ^ ((uVar2 & 0xff00) << 8 | uVar2 >> 0x18 | uVar2 >> 8 & 0xff00 |
				                     uVar2 << 0x18);
				uVar2 = uVar2 * 0x41a609fb + 0x2319;
				puVar1 = (uint *)((ulonglong)ioData + uVar3 * 4 + 4);
				*puVar1 = *puVar1 ^ ((uVar2 & 0xff00) << 8 | uVar2 >> 0x18 | uVar2 >> 8 & 0xff00 |
				                     uVar2 * 0x1000000);
				uVar2 = uVar2 * 0x41a609fb + 0x2319;
				puVar1 = (uint *)((ulonglong)ioData + uVar3 * 4 + 8);
				*puVar1 = *puVar1 ^ ((uVar2 & 0xff00) << 8 | uVar2 >> 0x18 | uVar2 >> 8 & 0xff00 |
				                     uVar2 * 0x1000000);
				uVar2 = uVar2 * 0x41a609fb + 0x2319;
				puVar1 = (uint *)((ulonglong)ioData + uVar3 * 4 + 0xc);
				*puVar1 = *puVar1 ^ ((uVar2 & 0xff00) << 8 | uVar2 >> 0x18 | uVar2 >> 8 & 0xff00 |
				                     uVar2 * 0x1000000);
				uVar2 = uVar2 * 0x41a609fb + 0x2319;
				puVar1 = (uint *)((ulonglong)ioData + uVar3 * 4 + 0x10);
				*puVar1 = *puVar1 ^ ((uVar2 & 0xff00) << 8 | uVar2 >> 0x18 | uVar2 >> 8 & 0xff00 |
				                     uVar2 * 0x1000000);
				uVar2 = uVar2 * 0x41a609fb + 0x2319;
				puVar1 = (uint *)((ulonglong)ioData + uVar3 * 4 + 0x14);
				*puVar1 = *puVar1 ^ ((uVar2 & 0xff00) << 8 | uVar2 >> 0x18 | uVar2 >> 8 & 0xff00 |
				                     uVar2 * 0x1000000);
				uVar2 = uVar2 * 0x41a609fb + 0x2319;
				puVar1 = (uint *)((ulonglong)ioData + uVar3 * 4 + 0x18);
				*puVar1 = *puVar1 ^ ((uVar2 & 0xff00) << 8 | uVar2 >> 0x18 | uVar2 >> 8 & 0xff00 |
				                     uVar2 * 0x1000000);
				uVar2 = uVar2 * 0x41a609fb + 0x2319;
				puVar1 = (uint *)((ulonglong)ioData + uVar3 * 4 + 0x1c);
				*puVar1 = *puVar1 ^ ((uVar2 & 0xff00) << 8 | uVar2 >> 0x18 | uVar2 >> 8 & 0xff00 |
				                     uVar2 * 0x1000000);
				uVar3 = uVar3 + 8;
				uVar2 = uVar2 * 0x41a609fb + 0x2319;
			} while (uVar3 < uVar4 - 8);
		}
		for (; uVar3 < uVar4; uVar3 = uVar3 + 1)
		{
			puVar1 = (uint *)((ulonglong)ioData + uVar3 * 4);
			*puVar1 = *puVar1 ^
			          ((uVar2 & 0xff00) << 8 | uVar2 >> 0x18 | uVar2 >> 8 & 0xff00 | uVar2 << 0x18);
			uVar2 = uVar2 * 0x41a609fb + 0x2319;
		}
	}
	return;
}
