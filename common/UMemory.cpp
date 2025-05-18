#include "UMemory.h"
#include "UError.h"

#ifndef _WIN32
#include <cstdlib>
#include <cstring>
#endif

// AppearanceEdit.app: 1009011c
// AppearanceEdit.exe: 004602fc
// KDXClient.exe: 004fed7c
// KDXClient.lexe: 081a0c40
// KDXServer.app: 1009d3ac
// KDXServer.command: 000e4edc
static uint gHandleCount = 0;

// KDXClient.lexe: 08152020
// KDXServer.exe: 004812c8
static const uint ccitt32_crctab[256] = {
    0x00000000, 0x04C11DB7, 0x09823B6E, 0x0D4326D9, 0x130476DC, 0x17C56B6B, 0x1A864DB2, 0x1E475005,
    0x2608EDB8, 0x22C9F00F, 0x2F8AD6D6, 0x2B4BCB61, 0x350C9B64, 0x31CD86D3, 0x3C8EA00A, 0x384FBDBD,
    0x4C11DB70, 0x48D0C6C7, 0x4593E01E, 0x4152FDA9, 0x5F15ADAC, 0x5BD4B01B, 0x569796C2, 0x52568B75,
    0x6A1936C8, 0x6ED82B7F, 0x639B0DA6, 0x675A1011, 0x791D4014, 0x7DDC5DA3, 0x709F7B7A, 0x745E66CD,
    0x9823B6E0, 0x9CE2AB57, 0x91A18D8E, 0x95609039, 0x8B27C03C, 0x8FE6DD8B, 0x82A5FB52, 0x8664E6E5,
    0xBE2B5B58, 0xBAEA46EF, 0xB7A96036, 0xB3687D81, 0xAD2F2D84, 0xA9EE3033, 0xA4AD16EA, 0xA06C0B5D,
    0xD4326D90, 0xD0F37027, 0xDDB056FE, 0xD9714B49, 0xC7361B4C, 0xC3F706FB, 0xCEB42022, 0xCA753D95,
    0xF23A8028, 0xF6FB9D9F, 0xFBB8BB46, 0xFF79A6F1, 0xE13EF6F4, 0xE5FFEB43, 0xE8BCCD9A, 0xEC7DD02D,
    0x34867077, 0x30476DC0, 0x3D044B19, 0x39C556AE, 0x278206AB, 0x23431B1C, 0x2E003DC5, 0x2AC12072,
    0x128E9DCF, 0x164F8078, 0x1B0CA6A1, 0x1FCDBB16, 0x018AEB13, 0x054BF6A4, 0x0808D07D, 0x0CC9CDCA,
    0x7897AB07, 0x7C56B6B0, 0x71159069, 0x75D48DDE, 0x6B93DDDB, 0x6F52C06C, 0x6211E6B5, 0x66D0FB02,
    0x5E9F46BF, 0x5A5E5B08, 0x571D7DD1, 0x53DC6066, 0x4D9B3063, 0x495A2DD4, 0x44190B0D, 0x40D816BA,
    0xACA5C697, 0xA864DB20, 0xA527FDF9, 0xA1E6E04E, 0xBFA1B04B, 0xBB60ADFC, 0xB6238B25, 0xB2E29692,
    0x8AAD2B2F, 0x8E6C3698, 0x832F1041, 0x87EE0DF6, 0x99A95DF3, 0x9D684044, 0x902B669D, 0x94EA7B2A,
    0xE0B41DE7, 0xE4750050, 0xE9362689, 0xEDF73B3E, 0xF3B06B3B, 0xF771768C, 0xFA325055, 0xFEF34DE2,
    0xC6BCF05F, 0xC27DEDE8, 0xCF3ECB31, 0xCBFFD686, 0xD5B88683, 0xD1799B34, 0xDC3ABDED, 0xD8FBA05A,
    0x690CE0EE, 0x6DCDFD59, 0x608EDB80, 0x644FC637, 0x7A089632, 0x7EC98B85, 0x738AAD5C, 0x774BB0EB,
    0x4F040D56, 0x4BC510E1, 0x46863638, 0x42472B8F, 0x5C007B8A, 0x58C1663D, 0x558240E4, 0x51435D53,
    0x251D3B9E, 0x21DC2629, 0x2C9F00F0, 0x285E1D47, 0x36194D42, 0x32D850F5, 0x3F9B762C, 0x3B5A6B9B,
    0x0315D626, 0x07D4CB91, 0x0A97ED48, 0x0E56F0FF, 0x1011A0FA, 0x14D0BD4D, 0x19939B94, 0x1D528623,
    0xF12F560E, 0xF5EE4BB9, 0xF8AD6D60, 0xFC6C70D7, 0xE22B20D2, 0xE6EA3D65, 0xEBA91BBC, 0xEF68060B,
    0xD727BBB6, 0xD3E6A601, 0xDEA580D8, 0xDA649D6F, 0xC423CD6A, 0xC0E2D0DD, 0xCDA1F604, 0xC960EBB3,
    0xBD3E8D7E, 0xB9FF90C9, 0xB4BCB610, 0xB07DABA7, 0xAE3AFBA2, 0xAAFBE615, 0xA7B8C0CC, 0xA379DD7B,
    0x9B3660C6, 0x9FF77D71, 0x92B45BA8, 0x9675461F, 0x8832161A, 0x8CF30BAD, 0x81B02D74, 0x857130C3,
    0x5D8A9099, 0x594B8D2E, 0x5408ABF7, 0x50C9B640, 0x4E8EE645, 0x4A4FFBF2, 0x470CDD2B, 0x43CDC09C,
    0x7B827D21, 0x7F436096, 0x7200464F, 0x76C15BF8, 0x68860BFD, 0x6C47164A, 0x61043093, 0x65C52D24,
    0x119B4BE9, 0x155A565E, 0x18197087, 0x1CD86D30, 0x029F3D35, 0x065E2082, 0x0B1D065B, 0x0FDC1BEC,
    0x3793A651, 0x3352BBE6, 0x3E119D3F, 0x3AD08088, 0x2497D08D, 0x2056CD3A, 0x2D15EBE3, 0x29D4F654,
    0xC5A92679, 0xC1683BCE, 0xCC2B1D17, 0xC8EA00A0, 0xD6AD50A5, 0xD26C4D12, 0xDF2F6BCB, 0xDBEE767C,
    0xE3A1CBC1, 0xE760D676, 0xEA23F0AF, 0xEEE2ED18, 0xF0A5BD1D, 0xF464A0AA, 0xF9278673, 0xFDE69BC4,
    0x89B8FD09, 0x8D79E0BE, 0x803AC667, 0x84FBDBD0, 0x9ABC8BD5, 0x9E7D9662, 0x933EB0BB, 0x97FFAD0C,
    0xAFB010B1, 0xAB710D06, 0xA6322BDF, 0xA2F33668, 0xBCB4666D, 0xB8757BDA, 0xB5365D03, 0xB1F740B4};

// KDXClient.lexe: 080c6af4
uint UMemory::AdlerSum(const void *inData, uint inDataSize, uint inInit)
{
	int iVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	int iVar8;
	int iVar9;
	int iVar10;
	int iVar11;
	int iVar12;
	int iVar13;
	int iVar14;
	int iVar15;
	uint uVar16;
	uint uVar17;
	uint uVar18;

	uVar17 = inInit & 0xffff;
	uVar16 = inInit >> 0x10;
	if (inDataSize != 0)
	{
		do
		{
			uVar18 = inDataSize;
			if (0x15b0 < inDataSize)
			{
				uVar18 = 0x15b0;
			}
			inDataSize = inDataSize - uVar18;
			for (; 0xf < (int)uVar18; uVar18 = uVar18 - 0x10)
			{
				iVar1 = uVar17 + *(byte *)inData;
				iVar2 = iVar1 + (uint) * (byte *)((ulonglong)inData + 1);
				iVar3 = iVar2 + (uint) * (byte *)((ulonglong)inData + 2);
				iVar4 = iVar3 + (uint) * (byte *)((ulonglong)inData + 3);
				iVar5 = iVar4 + (uint) * (byte *)((ulonglong)inData + 4);
				iVar6 = iVar5 + (uint) * (byte *)((ulonglong)inData + 5);
				iVar7 = iVar6 + (uint) * (byte *)((ulonglong)inData + 6);
				iVar8 = iVar7 + (uint) * (byte *)((ulonglong)inData + 7);
				iVar9 = iVar8 + (uint) * (byte *)((ulonglong)inData + 8);
				iVar10 = iVar9 + (uint) * (byte *)((ulonglong)inData + 9);
				iVar11 = iVar10 + (uint) * (byte *)((ulonglong)inData + 10);
				iVar12 = iVar11 + (uint) * (byte *)((ulonglong)inData + 0xb);
				iVar13 = iVar12 + (uint) * (byte *)((ulonglong)inData + 0xc);
				iVar14 = iVar13 + (uint) * (byte *)((ulonglong)inData + 0xd);
				iVar15 = iVar14 + (uint) * (byte *)((ulonglong)inData + 0xe);
				uVar17 = iVar15 + (uint) * (byte *)((ulonglong)inData + 0xf);
				uVar16 = uVar16 + iVar1 + iVar2 + iVar3 + iVar4 + iVar5 + iVar6 + iVar7 + iVar8 +
				         iVar9 + iVar10 + iVar11 + iVar12 + iVar13 + iVar14 + iVar15 + uVar17;
				inData = (void *)((ulonglong)inData + 0x10);
			}
			for (; uVar18 != 0; uVar18 = uVar18 - 1)
			{
				uVar17 = uVar17 + *(byte *)inData;
				inData = (void *)((ulonglong)inData + 1);
				uVar16 = uVar16 + uVar17;
			}
			uVar17 = uVar17 % 0xfff1;
			uVar16 = uVar16 % 0xfff1;
		} while (inDataSize != 0);
	}
	return uVar16 << 0x10 | uVar17;
}

// AppearanceEdit.app: 10008a90
// KDXClient.lexe: 080c6c24
// KDXServer.exe: 00435000
uint UMemory::Checksum(const void *inData, uint inDataSize, uint inInit)
{
	byte bVar1;
	uint uVar2;
	uint uVar3;
	uint uVar4;
	uint uVar5;
	uint uVar6;
	uint uVar7;
	uint uVar8;
	uint uVar9;
	byte *pbVar10;
	uint uVar11;
	uint uVar12;

	uVar11 = -(ulonglong)inData & 3U;
	if (inDataSize <= (-(ulonglong)inData & 3U))
	{
		uVar11 = inDataSize;
	}
	pbVar10 = (byte *)inData;
	if (uVar11 != 0)
	{
		pbVar10 = (byte *)((ulonglong)inData + 1);
		inInit = inInit * 0x1000193 ^ *(uint *)inData;
		if (1 < uVar11)
		{
			bVar1 = *pbVar10;
			pbVar10 = (byte *)((ulonglong)inData + 2);
			inInit = inInit * 0x1000193 ^ (uint)bVar1;
			if (2 < uVar11)
			{
				inInit = inInit * 0x1000193 ^ (uint)*pbVar10;
				pbVar10 = (byte *)((ulonglong)inData + 3);
			}
		}
		inDataSize = inDataSize - uVar11;
	}
	uVar12 = inDataSize >> 2;
	uVar11 = 0;
	if (uVar12 != 0)
	{
		if (8 < uVar12)
		{
			do
			{
				uVar2 = *(uint *)(pbVar10 + uVar11 * 4);
				uVar3 = *(uint *)(pbVar10 + uVar11 * 4 + 4);
				uVar4 = *(uint *)(pbVar10 + uVar11 * 4 + 8);
				uVar5 = *(uint *)(pbVar10 + uVar11 * 4 + 0xc);
				uVar6 = *(uint *)(pbVar10 + uVar11 * 4 + 0x10);
				uVar7 = *(uint *)(pbVar10 + uVar11 * 4 + 0x14);
				uVar8 = *(uint *)(pbVar10 + uVar11 * 4 + 0x18);
				uVar9 = *(uint *)(pbVar10 + uVar11 * 4 + 0x1c);
				uVar11 = uVar11 + 8;
				inInit =
				    (((((((((((((((((((((((((((((((inInit * 0x1000193 ^ uVar2 & 0xff) * 0x1000193 ^
				                                  uVar2 >> 8 & 0xff) *
				                                     0x1000193 ^
				                                 uVar2 >> 0x10 & 0xff) *
				                                    0x1000193 ^
				                                uVar2 >> 0x18) *
				                                   0x1000193 ^
				                               uVar3 & 0xff) *
				                                  0x1000193 ^
				                              uVar3 >> 8 & 0xff) *
				                                 0x1000193 ^
				                             uVar3 >> 0x10 & 0xff) *
				                                0x1000193 ^
				                            uVar3 >> 0x18) *
				                               0x1000193 ^
				                           uVar4 & 0xff) *
				                              0x1000193 ^
				                          uVar4 >> 8 & 0xff) *
				                             0x1000193 ^
				                         uVar4 >> 0x10 & 0xff) *
				                            0x1000193 ^
				                        uVar4 >> 0x18) *
				                           0x1000193 ^
				                       uVar5 & 0xff) *
				                          0x1000193 ^
				                      uVar5 >> 8 & 0xff) *
				                         0x1000193 ^
				                     uVar5 >> 0x10 & 0xff) *
				                        0x1000193 ^
				                    uVar5 >> 0x18) *
				                       0x1000193 ^
				                   uVar6 & 0xff) *
				                      0x1000193 ^
				                  uVar6 >> 8 & 0xff) *
				                     0x1000193 ^
				                 uVar6 >> 0x10 & 0xff) *
				                    0x1000193 ^
				                uVar6 >> 0x18) *
				                   0x1000193 ^
				               uVar7 & 0xff) *
				                  0x1000193 ^
				              uVar7 >> 8 & 0xff) *
				                 0x1000193 ^
				             uVar7 >> 0x10 & 0xff) *
				                0x1000193 ^
				            uVar7 >> 0x18) *
				               0x1000193 ^
				           uVar8 & 0xff) *
				              0x1000193 ^
				          uVar8 >> 8 & 0xff) *
				             0x1000193 ^
				         uVar8 >> 0x10 & 0xff) *
				            0x1000193 ^
				        uVar8 >> 0x18) *
				           0x1000193 ^
				       uVar9 & 0xff) *
				          0x1000193 ^
				      uVar9 >> 8 & 0xff) *
				         0x1000193 ^
				     uVar9 >> 0x10 & 0xff) *
				        0x1000193 ^
				    uVar9 >> 0x18;
			} while (uVar11 < uVar12 - 8);
		}
		for (; uVar11 < uVar12; uVar11 = uVar11 + 1)
		{
			uVar2 = *(uint *)(pbVar10 + uVar11 * 4);
			inInit =
			    (((inInit * 0x1000193 ^ uVar2 & 0xff) * 0x1000193 ^ uVar2 >> 8 & 0xff) * 0x1000193 ^
			     uVar2 >> 0x10 & 0xff) *
			        0x1000193 ^
			    uVar2 >> 0x18;
		}
	}
	uVar11 = inDataSize & 3;
	if (uVar11 != 0)
	{
		pbVar10 = pbVar10 + (inDataSize & 0xfffffffc);
		inInit = inInit * 0x1000193 ^ (uint)*pbVar10;
		if (1 < uVar11)
		{
			inInit = inInit * 0x1000193 ^ (uint)pbVar10[1];
			if (2 < uVar11)
			{
				inInit = inInit * 0x1000193 ^ (uint)pbVar10[2];
			}
		}
	}
	return inInit;
}

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

// KDXServer.exe: 00434380
bool UMemory::Compare(const void *inDataA, const void *inDataB, uint inSize)
{
	short *psVar1;
	short *psVar2;
	uint uVar3;

	if ((inSize == 0) || (inDataA == inDataB))
	{
		return true;
	}
	if ((inDataA != NULL) && (inDataB != NULL))
	{
		uVar3 = -(ulonglong)inDataA & 3;
		if (uVar3 != (-(ulonglong)inDataB & 3U))
		{
			uVar3 = 0;
			if (inSize != 0)
			{
				do
				{
					if (*(char *)(uVar3 + (ulonglong)inDataA) !=
					    *(char *)(uVar3 + (ulonglong)inDataB))
					{
						return false;
					}
					uVar3 = uVar3 + 1;
				} while (uVar3 < inSize);
			}
			return true;
		}
		if (inSize < uVar3)
		{
			uVar3 = inSize;
		}
		if (uVar3 != 0)
		{
			if (*(byte *)inDataA != *(byte *)inDataB)
			{
				return false;
			}
			if (1 < uVar3)
			{
				if (*(char *)((ulonglong)inDataA + 1) != *(char *)((ulonglong)inDataB + 1))
				{
					return false;
				}
				if ((2 < uVar3) &&
				    (*(char *)((ulonglong)inDataA + 2) != *(char *)((ulonglong)inDataB + 2)))
				{
					return false;
				}
			}
			inDataA = (void *)((ulonglong)inDataA + uVar3);
			inDataB = (void *)((ulonglong)inDataB + uVar3);
			inSize = inSize - uVar3;
		}
		uVar3 = 0;
		if (inSize >> 2 != 0)
		{
			do
			{
				if (*(int *)((ulonglong)inDataA + uVar3 * 4) !=
				    *(int *)((ulonglong)inDataB + uVar3 * 4))
				{
					return false;
				}
				uVar3 = uVar3 + 1;
			} while (uVar3 < inSize >> 2);
		}
		uVar3 = inSize & 3;
		if (uVar3 != 0)
		{
			psVar2 = (short *)((ulonglong)inDataA + (inSize & 0xfffffffc));
			psVar1 = (short *)((ulonglong)inDataB + (inSize & 0xfffffffc));
			if (uVar3 == 3)
			{
				if (*psVar2 != *psVar1)
				{
					return false;
				}
				if ((char)psVar2[1] != (char)psVar1[1])
				{
					return false;
				}
			}
			else if (uVar3 == 2)
			{
				if (*psVar2 != *psVar1)
				{
					return false;
				}
			}
			else if ((char)*psVar2 != (char)*psVar1)
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

// KDXClient.lexe: 080c6990
// KDXServer.exe: 00434ea0
uint UMemory::CRC(const void *inData, uint inDataSize, uint inInit)
{
	uint uVar1;
	uint uVar2;
	byte *pbVar3;
	uint uVar4;

	uVar4 = -(ulonglong)inData & 3U;
	if (inDataSize <= (-(ulonglong)inData & 3U))
	{
		uVar4 = inDataSize;
	}
	pbVar3 = (byte *)inData;
	if (uVar4 != 0)
	{
		inInit = inInit << 8 ^ ccitt32_crctab[inInit >> 0x18 ^ (uint) * (byte *)inData];
		pbVar3 = (byte *)((ulonglong)inData + 1);
		if (1 < uVar4)
		{
			inInit = inInit << 8 ^ ccitt32_crctab[inInit >> 0x18 ^ (uint)*pbVar3];
			pbVar3 = (byte *)((ulonglong)inData + 2);
			if (2 < uVar4)
			{
				inInit = inInit << 8 ^ ccitt32_crctab[inInit >> 0x18 ^ (uint)*pbVar3];
				pbVar3 = (byte *)((ulonglong)inData + 3);
			}
		}
		inDataSize = inDataSize - uVar4;
	}
	uVar4 = 0;
	if (inDataSize >> 2 != 0)
	{
		do
		{
			uVar1 = *(uint *)(pbVar3 + uVar4 * 4);
			uVar2 = inInit << 8 ^ ccitt32_crctab[inInit >> 0x18 ^ uVar1 & 0xff];
			uVar2 = uVar2 << 8 ^ ccitt32_crctab[uVar1 >> 8 & 0xff ^ uVar2 >> 0x18];
			uVar2 = uVar2 << 8 ^ ccitt32_crctab[uVar1 >> 0x10 & 0xff ^ uVar2 >> 0x18];
			uVar4 = uVar4 + 1;
			inInit = uVar2 << 8 ^ ccitt32_crctab[(uVar1 ^ uVar2) >> 0x18];
		} while (uVar4 < inDataSize >> 2);
	}
	uVar4 = inDataSize & 3;
	if (uVar4 != 0)
	{
		pbVar3 = pbVar3 + (inDataSize & 0xfffffffc);
		inInit = inInit << 8 ^ ccitt32_crctab[inInit >> 0x18 ^ (uint)*pbVar3];
		if (1 < uVar4)
		{
			inInit = inInit << 8 ^ ccitt32_crctab[inInit >> 0x18 ^ (uint)pbVar3[1]];
			if (2 < uVar4)
			{
				inInit = inInit << 8 ^ ccitt32_crctab[inInit >> 0x18 ^ (uint)pbVar3[2]];
			}
		}
	}
	return inInit;
}

// AppearanceEdit.app: 1004c120
// AppearanceEdit.exe: 00415080
// KDXClient.exe: 004577d0
// KDXClient.lexe: 08108cc0
// KDXServer.app: 1005e7c0
// KDXServer.command: 000176c8
void UMemory::Dispose(THdl inHdl)
{
	if (inHdl == NULL)
	{
		return;
	}
#ifdef _WIN32
	GlobalFree(inHdl);
#else
	// tweak: delete wrapper class
	delete inHdl;
#endif
	gHandleCount = gHandleCount - 1;
	return;
}

// KDXServer.exe: 00433e50
void UMemory::Fill(void *outDest, uint inSize, byte inByte)
{
	undefined8 uVar1;
	uint uVar2;
	uint uVar3;
	uint uVar4;

	uVar3 = (uint)inByte;
	if (uVar3 != 0)
	{
		uVar3 = uVar3 | uVar3 << 0x10 | uVar3 << 0x18 | uVar3 << 8;
	}
	uVar1 = CONCAT44(uVar3, uVar3);
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
							for (uVar4 = inSize >> 6; uVar4 != 0; uVar4 = uVar4 - 1)
							{
								*(undefined8 *)outDest = uVar1;
								*(undefined8 *)((ulonglong)outDest + 8) = uVar1;
								*(undefined8 *)((ulonglong)outDest + 0x10) = uVar1;
								*(undefined8 *)((ulonglong)outDest + 0x18) = uVar1;
								*(undefined8 *)((ulonglong)outDest + 0x20) = uVar1;
								*(undefined8 *)((ulonglong)outDest + 0x28) = uVar1;
								*(undefined8 *)((ulonglong)outDest + 0x30) = uVar1;
								*(undefined8 *)((ulonglong)outDest + 0x38) = uVar1;
								outDest = (void *)((ulonglong)outDest + 0x40);
							}
							if (0x1f < uVar2)
							{
								*(undefined8 *)outDest = uVar1;
								*(undefined8 *)((ulonglong)outDest + 8) = uVar1;
								*(undefined8 *)((ulonglong)outDest + 0x10) = uVar1;
								*(undefined8 *)((ulonglong)outDest + 0x18) = uVar1;
								outDest = (void *)((ulonglong)outDest + 0x20);
								uVar2 = uVar2 - 0x20;
							}
						}
						if ((((ulonglong)outDest & 0xf) != 0) || (uVar2 < 0x10))
							break;
						*(undefined8 *)outDest = uVar1;
						*(undefined8 *)((ulonglong)outDest + 8) = uVar1;
						outDest = (void *)((ulonglong)outDest + 0x10);
						inSize = uVar2 - 0x10;
					}
					if ((((ulonglong)outDest & 7) != 0) || (uVar2 < 8))
						break;
					*(undefined8 *)outDest = uVar1;
					outDest = (void *)((ulonglong)outDest + 8);
					inSize = uVar2 - 8;
				}
				if ((((ulonglong)outDest & 3) != 0) || (uVar2 < 4))
					break;
				*(uint *)outDest = uVar3;
				outDest = (void *)((ulonglong)outDest + 4);
				inSize = uVar2 - 4;
			}
			if ((((ulonglong)outDest & 1) != 0) || (uVar2 < 2))
				break;
			*(short *)outDest = (short)uVar3;
			outDest = (void *)((ulonglong)outDest + 2);
			inSize = uVar2 - 2;
		}
		if (uVar2 == 0)
			break;
		*(char *)outDest = (char)uVar3;
		outDest = (void *)((ulonglong)outDest + 1);
		inSize = uVar2 - 1;
	}
	return;
}

// AppearanceEdit.app: 10009050
// KDXServer.exe: 00433f80
void UMemory::Fill(void *outDest, uint inSize, ushort inWord)
{
	undefined8 uVar1;
	undefined4 uVar2;
	uint uVar3;
	uint uVar4;

	uVar2 = CONCAT22(inWord, inWord);
	uVar1 = CONCAT44(uVar2, uVar2);
	while (true)
	{
		while (true)
		{
			while (true)
			{
				while (true)
				{
					uVar4 = inSize;
					if (((ulonglong)outDest & 0x1f) == 0)
					{
						uVar4 = inSize & 0x1f;
						for (uVar3 = inSize >> 5; uVar3 != 0; uVar3 = uVar3 - 1)
						{
							*(undefined8 *)outDest = uVar1;
							*(undefined8 *)((ulonglong)outDest + 8) = uVar1;
							*(undefined8 *)((ulonglong)outDest + 0x10) = uVar1;
							*(undefined8 *)((ulonglong)outDest + 0x18) = uVar1;
							*(undefined8 *)((ulonglong)outDest + 0x20) = uVar1;
							*(undefined8 *)((ulonglong)outDest + 0x28) = uVar1;
							*(undefined8 *)((ulonglong)outDest + 0x30) = uVar1;
							*(undefined8 *)((ulonglong)outDest + 0x38) = uVar1;
							outDest = (void *)((ulonglong)outDest + 0x40);
						}
						if (0xf < uVar4)
						{
							*(undefined8 *)outDest = uVar1;
							*(undefined8 *)((ulonglong)outDest + 8) = uVar1;
							*(undefined8 *)((ulonglong)outDest + 0x10) = uVar1;
							*(undefined8 *)((ulonglong)outDest + 0x18) = uVar1;
							outDest = (void *)((ulonglong)outDest + 0x20);
							uVar4 = uVar4 - 0x10;
						}
					}
					if ((((ulonglong)outDest & 0xf) != 0) || (uVar4 < 8))
						break;
					*(undefined8 *)outDest = uVar1;
					*(undefined8 *)((ulonglong)outDest + 8) = uVar1;
					outDest = (void *)((ulonglong)outDest + 0x10);
					inSize = uVar4 - 8;
				}
				if ((((ulonglong)outDest & 7) != 0) || (uVar4 < 4))
					break;
				*(undefined8 *)outDest = uVar1;
				outDest = (void *)((ulonglong)outDest + 8);
				inSize = uVar4 - 4;
			}
			if ((((ulonglong)outDest & 3) != 0) || (uVar4 < 2))
				break;
			*(undefined4 *)outDest = uVar2;
			outDest = (void *)((ulonglong)outDest + 4);
			inSize = uVar4 - 2;
		}
		if (uVar4 == 0)
			break;
		*(ushort *)outDest = inWord;
		outDest = (void *)((ulonglong)outDest + 2);
		inSize = uVar4 - 1;
	}
	return;
}

// AppearanceEdit.app: 10009150
// KDXServer.exe: 00434080
void UMemory::Fill(void *outDest, uint inSize, uint inLong)
{
	undefined8 uVar1;
	uint uVar2;
	uint uVar3;

	uVar1 = CONCAT44(inLong, inLong);
	while (true)
	{
		while (true)
		{
			while (true)
			{
				uVar3 = inSize;
				if (((ulonglong)outDest & 0x1f) == 0)
				{
					uVar3 = inSize & 0xf;
					for (uVar2 = inSize >> 4; uVar2 != 0; uVar2 = uVar2 - 1)
					{
						*(undefined8 *)outDest = uVar1;
						*(undefined8 *)((ulonglong)outDest + 8) = uVar1;
						*(undefined8 *)((ulonglong)outDest + 0x10) = uVar1;
						*(undefined8 *)((ulonglong)outDest + 0x18) = uVar1;
						*(undefined8 *)((ulonglong)outDest + 0x20) = uVar1;
						*(undefined8 *)((ulonglong)outDest + 0x28) = uVar1;
						*(undefined8 *)((ulonglong)outDest + 0x30) = uVar1;
						*(undefined8 *)((ulonglong)outDest + 0x38) = uVar1;
						outDest = (void *)((ulonglong)outDest + 0x40);
					}
					if (7 < uVar3)
					{
						*(undefined8 *)outDest = uVar1;
						*(undefined8 *)((ulonglong)outDest + 8) = uVar1;
						*(undefined8 *)((ulonglong)outDest + 0x10) = uVar1;
						*(undefined8 *)((ulonglong)outDest + 0x18) = uVar1;
						outDest = (void *)((ulonglong)outDest + 0x20);
						uVar3 = uVar3 - 8;
					}
				}
				if ((((ulonglong)outDest & 0xf) != 0) || (uVar3 < 4))
					break;
				*(undefined8 *)outDest = uVar1;
				*(undefined8 *)((ulonglong)outDest + 8) = uVar1;
				outDest = (void *)((ulonglong)outDest + 0x10);
				inSize = uVar3 - 4;
			}
			if ((((ulonglong)outDest & 7) != 0) || (uVar3 < 2))
				break;
			*(undefined8 *)outDest = uVar1;
			outDest = (void *)((ulonglong)outDest + 8);
			inSize = uVar3 - 2;
		}
		if (uVar3 == 0)
			break;
		*(uint *)outDest = inLong;
		outDest = (void *)((ulonglong)outDest + 4);
		inSize = uVar3 - 1;
	}
	return;
}

// KDXServer.exe: 0042e470
longlong UMemory::GetHandleCount(uint *outCount)
{
	if (outCount != NULL)
	{
		*outCount = gHandleCount;
	}
	return 0;
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
THdl UMemory::NewHandle(uint inSize)
{
	THdl pvVar1;

	if (inSize == 0)
	{
		__Fail(0x10002);
	}
#ifdef _WIN32
	pvVar1 = GlobalAlloc(GMEM_FIXED, inSize);
#else
	pvVar1 = new THdlObj(inSize);
#endif // _WIN32
	if (pvVar1 == NULL)
	{
		__Fail(0x20065);
	}
	gHandleCount = gHandleCount + 1;
	return pvVar1;
}

// AppearanceEdit.exe: 00414ff0
// KDXClient.exe: 00457740
// KDXClient.lexe: 08108bf8
// KDXServer.app: 1005e6c0
// KDXServer.command: 000175c0
THdl UMemory::NewHandle(const void *inData, uint inSize)
{
	THdl pvVar1;

	if (inSize == 0)
	{
		__Fail(0x10002);
	}
#ifdef _WIN32
	pvVar1 = GlobalAlloc(GMEM_FIXED, inSize);
#else
	// tweak: use wrapper class
	pvVar1 = new THdlObj(inSize);
#endif // _WIN32
	if (pvVar1 == NULL)
	{
		__Fail(0x20065);
	}
	// tweak: use the inlined lock/unlock functions
	void *pvVar2 = UMemory::Lock(pvVar1);
	Move(pvVar2, inData, inSize);
	UMemory::Unlock(pvVar1);

	gHandleCount = gHandleCount + 1;
	return pvVar1;
}

// AppearanceEdit.app: 1004c0a0
// AppearanceEdit.exe: 00415040
// KDXClient.exe: 00457790
// KDXClient.lexe: 08108c5c
// KDXServer.app: 1005e750
// KDXServer.command: 00017648
THdl UMemory::NewHandleClear(uint inSize)
{
	THdl pvVar1;

	if (inSize == 0)
	{
		__Fail(0x10002);
	}
#ifdef _WIN32
	pvVar1 = GlobalAlloc(GMEM_ZEROINIT, inSize);
#else
	THdl pvVar1 = new THdlObj(inSize);
	UMemory::Clear(*pvVar1, inSize);
#endif
	if (pvVar1 == NULL)
	{
		__Fail(0x20065);
	}
	gHandleCount = gHandleCount + 1;
	return pvVar1;
}

// AppearanceEdit.exe: 004150b0
// KDXClient.exe: 00457800
// KDXClient.lexe: 08108cec
// KDXServer.command: 00017724
THdl UMemory::Reallocate(THdl inHdl, uint inSize)
{
	THdl pvVar1;

	if (inHdl == NULL)
	{
		pvVar1 = NULL;
		if (inSize != 0)
		{
			pvVar1 = NewHandle(inSize);
		}
	}
	else if (inSize == 0)
	{
		Dispose(inHdl);
		pvVar1 = NULL;
	}
	else
	{
#ifdef _WIN32
		pvVar1 = GlobalReAlloc(inHdl, inSize, 2);
#else
		*pvVar1 = std::realloc(*inHdl, inSize);
#endif
		if (pvVar1 == NULL)
		{
			__Fail(0x20065);
		}
	}
	return pvVar1;
}

// KDXServer.exe: 004345e0
void *UMemory::Search(const void *inSearchData, uint inSearchSize, const void *inData,
                      uint inDataSize)
{
	int iVar1;
	int iVar2;
	bool bVar3;
	char *pcVar4;
	uint uVar5;
	uint uVar6;
	uint local_418;
	int aiStack_410[256];

	if (((inDataSize < inSearchSize) || (inDataSize == 0)) || (inSearchSize == 0))
	{
		return NULL;
	}
	if (inSearchSize == 1)
	{
		pcVar4 = (char *)SearchByte(*(byte *)inSearchData, (char *)inData, inDataSize);
		return pcVar4;
	}
	if (inSearchSize != 2)
	{
		uVar5 = 0;
		do
		{
			iVar1 = inSearchSize + 1;
			aiStack_410[uVar5] = iVar1;
			aiStack_410[uVar5 + 2] = iVar1;
			aiStack_410[uVar5 + 3] = iVar1;
			aiStack_410[uVar5 + 1] = iVar1;
			aiStack_410[uVar5 + 4] = iVar1;
			aiStack_410[uVar5 + 5] = iVar1;
			aiStack_410[uVar5 + 6] = iVar1;
			aiStack_410[uVar5 + 7] = iVar1;
			uVar5 = uVar5 + 8;
		} while (uVar5 < 0x100);
		uVar5 = 0;
		if (inSearchSize != 0)
		{
			if (8 < inSearchSize)
			{
				do
				{
					aiStack_410[*(byte *)(uVar5 + (ulonglong)inSearchData)] = inSearchSize - uVar5;
					aiStack_410[*(byte *)((ulonglong)inSearchData + uVar5 + 1)] =
					    inSearchSize - (uVar5 + 1);
					aiStack_410[*(byte *)((ulonglong)inSearchData + uVar5 + 2)] =
					    inSearchSize - (uVar5 + 2);
					aiStack_410[*(byte *)((ulonglong)inSearchData + uVar5 + 3)] =
					    inSearchSize - (uVar5 + 3);
					aiStack_410[*(byte *)((ulonglong)inSearchData + uVar5 + 4)] =
					    inSearchSize - (uVar5 + 4);
					aiStack_410[*(byte *)((ulonglong)inSearchData + uVar5 + 5)] =
					    inSearchSize - (uVar5 + 5);
					aiStack_410[*(byte *)((ulonglong)inSearchData + uVar5 + 6)] =
					    inSearchSize - (uVar5 + 6);
					iVar1 = uVar5 + 7;
					iVar2 = uVar5 + 7;
					uVar5 = uVar5 + 8;
					aiStack_410[*(byte *)((ulonglong)inSearchData + iVar2)] = inSearchSize - iVar1;
				} while (uVar5 < inSearchSize - 8);
			}
			for (; uVar5 < inSearchSize; uVar5 = uVar5 + 1)
			{
				aiStack_410[*(byte *)(uVar5 + (ulonglong)inSearchData)] = inSearchSize - uVar5;
			}
		}
		local_418 = 0;
		if (inDataSize != inSearchSize)
		{
			do
			{
				bVar3 =
				    Compare(inSearchData, (void *)((ulonglong)inData + local_418), inSearchSize);
				if (bVar3)
				{
					return (void *)((ulonglong)inData + local_418);
				}
				local_418 = local_418 +
				            aiStack_410[*(byte *)((ulonglong)inData + local_418 + inSearchSize)];
			} while (local_418 < inDataSize - inSearchSize);
		}
		if (local_418 == inDataSize - inSearchSize)
		{
			bVar3 = Compare(inSearchData, (void *)((ulonglong)inData + local_418), inSearchSize);
			if (bVar3)
			{
				return (void *)((ulonglong)inData + local_418);
			}
		}
		return NULL;
	}
	uVar5 = (uint) * (byte *)inData;
	uVar6 = 1;
	if (1 < inDataSize)
	{
		do
		{
			uVar5 = (uVar5 & 0xff) << 8 | (uint) * (byte *)(uVar6 + (ulonglong)inData);
			if (uVar5 ==
			    CONCAT11(*(byte *)inSearchData, *(undefined1 *)((ulonglong)inSearchData + 1)))
			{
				return (void *)((ulonglong)inData + (uVar6 - 1));
			}
			uVar6 = uVar6 + 1;
		} while (uVar6 < inDataSize);
	}
	return NULL;
}

// KDXServer.exe: 00434880
byte *UMemory::SearchByte(byte inByte, const void *inData, uint inSize)
{
	if (inSize != 0)
	{
		do
		{
			inSize = inSize - 1;
			if (*(byte *)inData == inByte)
			{
				return (byte *)inData;
			}
			inData = (byte *)((ulonglong)inData + 1);
		} while (inSize != 0);
	}
	return NULL;
}

// KDXServer.exe: 004348b0
byte *UMemory::SearchByteBackwards(byte inByte, const void *inData, uint inDataSize)
{
	byte *pbVar1;

	pbVar1 = (byte *)((ulonglong)inData + inDataSize);
	if (inDataSize != 0)
	{
		do
		{
			inDataSize = inDataSize - 1;
			pbVar1 = pbVar1 + -1;
			if (*pbVar1 == inByte)
			{
				return pbVar1;
			}
		} while (inDataSize != 0);
	}
	return NULL;
}
