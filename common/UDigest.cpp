#include "UDigest.h"
#include "UMemory.h"

// KDXClient.exe: 004d4ae0
static const byte bufEncodingTable64[] =
    "aADQEHILXNOp8q+rstPRS523F0VWYhZ7bcdBe/fgijkMlmnJouGvwxyKz1469TU\0\0\0\0";

// KDXClient.exe: 00500610
static const byte bufEncodingTable80[80] = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xaa, 0xaa, 0xff, 0xff, 0xaa, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xaa, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0xff, 0xff, 0xff, 0x26,
    0x1a, 0x3a, 0x17, 0x18, 0x3b, 0x16, 0x3c, 0x20, 0x0d, 0x3d, 0xff, 0xff, 0xff, 0xbb, 0xff, 0xff,
    0xff, 0x02, 0x24, 0x00, 0x03, 0x05, 0x19, 0x33, 0x06, 0x07, 0x30, 0x38, 0x08, 0x2c, 0x0a, 0x0b};

// KDXClient.exe: 00472430
uint UDigest::Base64_Encode(const void *inData, uint inDataSize, void *outData)
{
	byte bVar1;
	byte bVar2;
	byte *pbVar3;
	byte *pbVar4;
	uint uVar5;
	int iVar6;

	iVar6 = 0;
	pbVar3 = (byte *)outData;
	pbVar4 = (byte *)outData;
	if (2 < inDataSize)
	{
		do
		{
			uVar5 = (uint) * (byte *)((ulonglong)inData + 1) << 8 | (uint) * (byte *)inData << 0x10;
			bVar1 = *(byte *)((ulonglong)inData + 2);
			*pbVar3 = bufEncodingTable64[(((uint) * (byte *)inData << 0x10) >> 0x12) - 1];
			pbVar3[1] = bufEncodingTable64[((uVar5 & 0x3f000) >> 0xc) - 1];
			pbVar3[2] = bufEncodingTable64[((uVar5 | bVar1) >> 6 & 0x3f) - 1];
			iVar6 = iVar6 + 4;
			pbVar3[3] = bufEncodingTable64[(bVar1 & 0x3f) - 1];
			inData = (void *)((ulonglong)inData + 3);
			pbVar4 = pbVar3 + 4;
			inDataSize = inDataSize - 3;
			if (iVar6 == 0x3c)
			{
				iVar6 = 0;
				*pbVar4 = 0xd;
				pbVar4 = pbVar3 + 5;
			}
			pbVar3 = pbVar4;
		} while (2 < inDataSize);
	}
	if (inDataSize == 2)
	{
		bVar1 = *(byte *)((ulonglong)inData + 1);
		bVar2 = *(byte *)inData;
		*pbVar4 = bufEncodingTable64[(((uint)bVar2 << 0x10) >> 0x12) - 1];
		pbVar4[1] =
		    bufEncodingTable64[(((uint)bVar1 << 8 | (uint)bVar2 << 0x10) >> 0xc & 0x3f) - 1];
		pbVar4[2] = bufEncodingTable64[(((uint)bVar1 << 8 & 0xfc0) >> 6) - 1];
	}
	else
	{
		if (inDataSize != 1)
			goto LAB_00472527;
		bVar1 = *(byte *)inData;
		*pbVar4 = bufEncodingTable64[(((uint)bVar1 << 0x10) >> 0x12) - 1];
		pbVar4[1] = bufEncodingTable64[(((uint)bVar1 << 0x10) >> 0xc & 0x3f) - 1];
		pbVar4[2] = 0x3d;
	}
	pbVar4[3] = 0x3d;
	pbVar4 = pbVar4 + 4;
	iVar6 = iVar6 + 4;
LAB_00472527:
	if (iVar6 != 0)
	{
		*pbVar4 = 0xd;
		pbVar4 = pbVar4 + 1;
	}
	return (ulonglong)pbVar4 + -(ulonglong)outData;
}

// KDXClient.exe: 00472540
void *UDigest::Base80_Decode(const void *inData, uint inDataSize, uint *outDataSize)
{
	uint uVar1;
	uint uVar2;
	uint *puVar3;
	uint uVar4;
	int iVar5;
	byte *pbVar6;

	pbVar6 = (byte *)((ulonglong)inData + inDataSize);
	uVar1 = 0;
	iVar5 = 0;
	puVar3 = outDataSize;
	if (inData < pbVar6)
	{
		do
		{
			uVar4 = (uint)bufEncodingTable80[*(byte *)inData & 0x7f];
			inData = (void *)((ulonglong)inData + 1);
			if (uVar4 < 0x40)
			{
				uVar2 = uVar1 << 6;
				iVar5 = iVar5 + 1;
				uVar1 = uVar2 | uVar4;
				if (iVar5 == 4)
				{
					*(char *)puVar3 = (char)(uVar2 >> 0x10);
					*(char *)((ulonglong)puVar3 + 1) = (char)(uVar2 >> 8);
					*(char *)((ulonglong)puVar3 + 2) = (char)uVar1;
					puVar3 = (uint *)((ulonglong)puVar3 + 3);
					iVar5 = 0;
					uVar1 = 0;
				}
			}
			else if (uVar4 != 0xaa)
			{
				if (uVar4 != 0xbb)
				{
					return NULL;
				}
				break;
			}
		} while (inData < pbVar6);
	}
	if (iVar5 == 2)
	{
		*(char *)puVar3 = (char)(uVar1 >> 4);
		puVar3 = (uint *)((ulonglong)puVar3 + 1);
	}
	else if (iVar5 == 3)
	{
		*(char *)puVar3 = (char)(uVar1 >> 10);
		*(char *)((ulonglong)puVar3 + 1) = (char)(uVar1 >> 2);
		puVar3 = (uint *)((ulonglong)puVar3 + 2);
	}
	return (void *)((ulonglong)puVar3 - (ulonglong)outDataSize);
}

// KDXClient.lexe: 080de6a8
// KDXServer.exe: 0045c850
void UDigest::MD5_Encode(const void *inData, uint inDataSize, void *outDigest)
{
	_MD5 local_84;

	local_84.Init();
	local_84.Update(inData, inDataSize);
	local_84.Report(outDigest);
	return;
}

// KDXClient.lexe: 080c8100
// KDXServer.exe: 00434270
void _MD5::Clear(uint inSize)
{
	UMemory::Clear(this, inSize);
	// tweak: Empty function call removed:
	// KDXServer.exe: FUN_00434260
	return;
}

// KDXClient.lexe: 080de710
// KDXServer.exe: 00434280
void _MD5::Init()
{
	mState[0] = 0x64452301;
	mState[1] = 0xefcdab89;
	mState[2] = 0x98badcfe;
	mState[3] = 0x10325476;
	mState[4] = 0xc3d2e1f0;
	mCount = 0;
	mBufferLength = 0;
	return;
}

// KDXClient.lexe: 080de844
// KDXServer.exe: 0045c9a0
void _MD5::Report(void *outDigest)
{
	int iVar1;
	uint uVar2;
	uint uVar3;
	int iVar4;

	Update(NULL, 0);
	uVar3 = mCount;
	uVar2 = uVar3 * 0x40;
	iVar4 = (uint)(uVar2 < uVar3) + (uVar3 >> 0x1a);
	uVar3 = uVar2 + mBufferLength;
	if (uVar3 < uVar2)
	{
		iVar4 = iVar4 + 1;
	}
	uVar2 = uVar3 * 8;
	if (uVar2 < uVar3)
	{
		iVar4 = iVar4 + 1;
	}
	iVar4 = iVar4 + (uVar3 >> 0x1d);
	if (mBufferLength < 0x38)
	{
		iVar1 = mBufferLength;
		mBufferLength = mBufferLength + 1;
		mBuffer[iVar1] = 0x80;
		iVar1 = mBufferLength;
		while (iVar1 < 0x38)
		{
			iVar1 = mBufferLength;
			mBufferLength = mBufferLength + 1;
			mBuffer[iVar1] = '\0';
			iVar1 = mBufferLength;
		}
	}
	else
	{
		iVar1 = mBufferLength;
		mBufferLength = mBufferLength + 1;
		mBuffer[iVar1] = 0x80;
		iVar1 = mBufferLength;
		while (iVar1 < 0x40)
		{
			iVar1 = mBufferLength;
			mBufferLength = mBufferLength + 1;
			mBuffer[iVar1] = '\0';
			iVar1 = mBufferLength;
		}
		Update(NULL, 0);
		mBuffer[0] = '\0';
		mBuffer[1] = '\0';
		mBuffer[2] = '\0';
		mBuffer[3] = '\0';
		mBuffer[4] = '\0';
		mBuffer[5] = '\0';
		mBuffer[6] = '\0';
		mBuffer[7] = '\0';
		mBuffer[8] = '\0';
		mBuffer[9] = '\0';
		mBuffer[10] = '\0';
		mBuffer[0xb] = '\0';
		mBuffer[0xc] = '\0';
		mBuffer[0xd] = '\0';
		mBuffer[0xe] = '\0';
		mBuffer[0xf] = '\0';
		mBuffer[0x10] = '\0';
		mBuffer[0x11] = '\0';
		mBuffer[0x12] = '\0';
		mBuffer[0x13] = '\0';
		mBuffer[0x14] = '\0';
		mBuffer[0x15] = '\0';
		mBuffer[0x16] = '\0';
		mBuffer[0x17] = '\0';
		mBuffer[0x18] = '\0';
		mBuffer[0x19] = '\0';
		mBuffer[0x1a] = '\0';
		mBuffer[0x1b] = '\0';
		mBuffer[0x1c] = '\0';
		mBuffer[0x1d] = '\0';
		mBuffer[0x1e] = '\0';
		mBuffer[0x1f] = '\0';
		mBuffer[0x20] = '\0';
		mBuffer[0x21] = '\0';
		mBuffer[0x22] = '\0';
		mBuffer[0x23] = '\0';
		mBuffer[0x24] = '\0';
		mBuffer[0x25] = '\0';
		mBuffer[0x26] = '\0';
		mBuffer[0x27] = '\0';
		mBuffer[0x28] = '\0';
		mBuffer[0x29] = '\0';
		mBuffer[0x2a] = '\0';
		mBuffer[0x2b] = '\0';
		mBuffer[0x2c] = '\0';
		mBuffer[0x2d] = '\0';
		mBuffer[0x2e] = '\0';
		mBuffer[0x2f] = '\0';
		mBuffer[0x30] = '\0';
		mBuffer[0x31] = '\0';
		mBuffer[0x32] = '\0';
		mBuffer[0x33] = '\0';
		mBuffer[0x34] = '\0';
		mBuffer[0x35] = '\0';
		mBuffer[0x36] = '\0';
		mBuffer[0x37] = '\0';
	}
	mBuffer[0x38] = (uchar)((uint)iVar4 >> 0x18);
	mBuffer[0x39] = (uchar)((uint)iVar4 >> 0x10);
	mBuffer[0x3a] = (uchar)((uint)iVar4 >> 8);
	mBuffer[0x3b] = (uchar)iVar4;
	mBuffer[0x3c] = (uchar)(uVar2 >> 0x18);
	mBuffer[0x3d] = (uchar)(uVar2 >> 0x10);
	mBuffer[0x3e] = (uchar)(uVar2 >> 8);
	mBuffer[0x3f] = (uchar)uVar2;
	Transform((const uint *)mBuffer);
	uVar3 = mState[0];
	*(uint *)outDigest =
	    (uVar3 & 0xff00) << 8 | uVar3 >> 0x18 | uVar3 >> 8 & 0xff00 | uVar3 << 0x18;
	uVar3 = mState[1];
	*(uint *)((ulonglong)outDigest + 4) =
	    (uVar3 & 0xff00) << 8 | uVar3 >> 0x18 | uVar3 >> 8 & 0xff00 | uVar3 << 0x18;
	uVar3 = mState[2];
	*(uint *)((ulonglong)outDigest + 8) =
	    (uVar3 & 0xff00) << 8 | uVar3 >> 0x18 | uVar3 >> 8 & 0xff00 | uVar3 << 0x18;
	uVar3 = mState[3];
	*(uint *)((ulonglong)outDigest + 0xc) =
	    (uVar3 & 0xff00) << 8 | uVar3 >> 0x18 | uVar3 >> 8 & 0xff00 | uVar3 << 0x18;
	uVar3 = mState[4];
	*(uint *)((ulonglong)outDigest + 0x10) =
	    (uVar3 & 0xff00) << 8 | uVar3 >> 0x18 | uVar3 >> 8 & 0xff00 | uVar3 << 0x18;
	Clear(sizeof(_MD5)); // tweak: ensure proper size of _MD5
	return;
}

// KDXClient.lexe: 080dea9c
// KDXServer.exe: 0045a370
void _MD5::Transform(const uint *inBlock)
{
	uint uVar1;
	uint uVar2;
	uint uVar3;
	uint uVar4;
	uint uVar5;
	uint uVar6;
	uint uVar7;
	uint uVar8;
	uint uVar9;
	uint uVar10;
	uint uVar11;
	uint uVar12;
	uint uVar13;
	uint uVar14;
	uint uVar15;
	uint uVar16;
	uint uVar17;
	uint uVar18;
	uint uVar19;
	uint uVar20;
	uint uVar21;
	uint uVar22;
	uint uVar23;

	uVar14 = mState[0];
	uVar22 = mState[1];
	uVar19 = mState[2];
	uVar10 = mState[3];
	uVar21 = *inBlock;
	uVar21 = (uVar21 & 0xff00) << 8 | uVar21 >> 0x18 | uVar21 >> 8 & 0xff00 | uVar21 << 0x18;
	uVar1 = inBlock[1];
	uVar1 = (uVar1 & 0xff00) << 8 | uVar1 >> 0x18 | uVar1 >> 8 & 0xff00 | uVar1 << 0x18;
	uVar18 = inBlock[2];
	uVar18 = (uVar18 & 0xff00) << 8 | uVar18 >> 0x18 | uVar18 >> 8 & 0xff00 | uVar18 << 0x18;
	uVar2 = inBlock[3];
	uVar2 = (uVar2 & 0xff00) << 8 | uVar2 >> 0x18 | uVar2 >> 8 & 0xff00 | uVar2 << 0x18;
	uVar12 = inBlock[4];
	uVar12 = (uVar12 & 0xff00) << 8 | uVar12 >> 0x18 | uVar12 >> 8 & 0xff00 | uVar12 << 0x18;
	uVar3 = inBlock[5];
	uVar3 = (uVar3 & 0xff00) << 8 | uVar3 >> 0x18 | uVar3 >> 8 & 0xff00 | uVar3 << 0x18;
	uVar4 = inBlock[6];
	uVar4 = (uVar4 & 0xff00) << 8 | uVar4 >> 0x18 | uVar4 >> 8 & 0xff00 | uVar4 << 0x18;
	uVar5 = inBlock[7];
	uVar5 = (uVar5 & 0xff00) << 8 | uVar5 >> 0x18 | uVar5 >> 8 & 0xff00 | uVar5 << 0x18;
	uVar13 = inBlock[8];
	uVar13 = (uVar13 & 0xff00) << 8 | uVar13 >> 0x18 | uVar13 >> 8 & 0xff00 | uVar13 << 0x18;
	uVar11 = inBlock[9];
	uVar11 = (uVar11 & 0xff00) << 8 | uVar11 >> 0x18 | uVar11 >> 8 & 0xff00 | uVar11 << 0x18;
	uVar17 = inBlock[10];
	uVar17 = (uVar17 & 0xff00) << 8 | uVar17 >> 0x18 | uVar17 >> 8 & 0xff00 | uVar17 << 0x18;
	uVar20 = inBlock[0xb];
	uVar20 = (uVar20 & 0xff00) << 8 | uVar20 >> 0x18 | uVar20 >> 8 & 0xff00 | uVar20 << 0x18;
	uVar6 = inBlock[0xc];
	uVar6 = (uVar6 & 0xff00) << 8 | uVar6 >> 0x18 | uVar6 >> 8 & 0xff00 | uVar6 << 0x18;
	uVar7 = inBlock[0xd];
	uVar7 = (uVar7 & 0xff00) << 8 | uVar7 >> 0x18 | uVar7 >> 8 & 0xff00 | uVar7 << 0x18;
	uVar8 = inBlock[0xe];
	uVar8 = (uVar8 & 0xff00) << 8 | uVar8 >> 0x18 | uVar8 >> 8 & 0xff00 | uVar8 << 0x18;
	uVar9 = inBlock[0xf];
	uVar9 = (uVar9 & 0xff00) << 8 | uVar9 >> 0x18 | uVar9 >> 8 & 0xff00 | uVar9 << 0x18;
	uVar15 = mState[4] + (uVar14 >> 0x1b | uVar14 << 5) + ((uVar19 ^ uVar10) & uVar22 ^ uVar10) +
	         0x5a827999 + uVar21;
	uVar22 = uVar22 >> 2 | uVar22 << 0x1e;
	uVar10 = uVar10 + (uVar15 >> 0x1b | uVar15 * 0x20) + ((uVar22 ^ uVar19) & uVar14 ^ uVar19) +
	         0x5a827999 + uVar1;
	uVar14 = uVar14 >> 2 | uVar14 << 0x1e;
	uVar19 = uVar19 + (uVar10 >> 0x1b | uVar10 * 0x20) + ((uVar14 ^ uVar22) & uVar15 ^ uVar22) +
	         0x5a827999 + uVar18;
	uVar15 = uVar15 >> 2 | uVar15 * 0x40000000;
	uVar22 = uVar22 + (uVar19 >> 0x1b | uVar19 * 0x20) + ((uVar15 ^ uVar14) & uVar10 ^ uVar14) +
	         0x5a827999 + uVar2;
	uVar10 = uVar10 >> 2 | uVar10 * 0x40000000;
	uVar14 = uVar14 + (uVar22 >> 0x1b | uVar22 * 0x20) + ((uVar10 ^ uVar15) & uVar19 ^ uVar15) +
	         0x5a827999 + uVar12;
	uVar19 = uVar19 >> 2 | uVar19 * 0x40000000;
	uVar15 = uVar15 + (uVar14 >> 0x1b | uVar14 * 0x20) + ((uVar19 ^ uVar10) & uVar22 ^ uVar10) +
	         0x5a827999 + uVar3;
	uVar22 = uVar22 >> 2 | uVar22 * 0x40000000;
	uVar10 = uVar10 + (uVar15 >> 0x1b | uVar15 * 0x20) + ((uVar22 ^ uVar19) & uVar14 ^ uVar19) +
	         0x5a827999 + uVar4;
	uVar14 = uVar14 >> 2 | uVar14 * 0x40000000;
	uVar19 = uVar19 + (uVar10 >> 0x1b | uVar10 * 0x20) + ((uVar14 ^ uVar22) & uVar15 ^ uVar22) +
	         0x5a827999 + uVar5;
	uVar15 = uVar15 >> 2 | uVar15 * 0x40000000;
	uVar22 = uVar22 + (uVar19 >> 0x1b | uVar19 * 0x20) + ((uVar15 ^ uVar14) & uVar10 ^ uVar14) +
	         0x5a827999 + uVar13;
	uVar10 = uVar10 >> 2 | uVar10 * 0x40000000;
	uVar14 = uVar14 + (uVar22 >> 0x1b | uVar22 * 0x20) + ((uVar10 ^ uVar15) & uVar19 ^ uVar15) +
	         0x5a827999 + uVar11;
	uVar19 = uVar19 >> 2 | uVar19 * 0x40000000;
	uVar15 = uVar15 + (uVar14 >> 0x1b | uVar14 * 0x20) + ((uVar19 ^ uVar10) & uVar22 ^ uVar10) +
	         0x5a827999 + uVar17;
	uVar22 = uVar22 >> 2 | uVar22 * 0x40000000;
	uVar10 = uVar10 + (uVar15 >> 0x1b | uVar15 * 0x20) + ((uVar22 ^ uVar19) & uVar14 ^ uVar19) +
	         0x5a827999 + uVar20;
	uVar14 = uVar14 >> 2 | uVar14 * 0x40000000;
	uVar19 = uVar19 + (uVar10 >> 0x1b | uVar10 * 0x20) + ((uVar14 ^ uVar22) & uVar15 ^ uVar22) +
	         0x5a827999 + uVar6;
	uVar15 = uVar15 >> 2 | uVar15 * 0x40000000;
	uVar22 = uVar22 + (uVar19 >> 0x1b | uVar19 * 0x20) + ((uVar15 ^ uVar14) & uVar10 ^ uVar14) +
	         0x5a827999 + uVar7;
	uVar10 = uVar10 >> 2 | uVar10 * 0x40000000;
	uVar14 = uVar14 + (uVar22 >> 0x1b | uVar22 * 0x20) + ((uVar10 ^ uVar15) & uVar19 ^ uVar15) +
	         0x5a827999 + uVar8;
	uVar19 = uVar19 >> 2 | uVar19 * 0x40000000;
	uVar15 = uVar15 + (uVar14 >> 0x1b | uVar14 * 0x20) + ((uVar19 ^ uVar10) & uVar22 ^ uVar10) +
	         0x5a827999 + uVar9;
	uVar22 = uVar22 >> 2 | uVar22 * 0x40000000;
	uVar21 = uVar21 ^ uVar18 ^ uVar13 ^ uVar7;
	uVar21 = uVar21 >> 0x1f | uVar21 << 1;
	uVar10 = uVar10 + (uVar15 >> 0x1b | uVar15 * 0x20) + ((uVar22 ^ uVar19) & uVar14 ^ uVar19) +
	         0x5a827999 + uVar21;
	uVar14 = uVar14 >> 2 | uVar14 * 0x40000000;
	uVar1 = uVar1 ^ uVar2 ^ uVar11 ^ uVar8;
	uVar1 = uVar1 >> 0x1f | uVar1 << 1;
	uVar19 = uVar19 + (uVar10 >> 0x1b | uVar10 * 0x20) + ((uVar14 ^ uVar22) & uVar15 ^ uVar22) +
	         0x5a827999 + uVar1;
	uVar15 = uVar15 >> 2 | uVar15 * 0x40000000;
	uVar18 = uVar18 ^ uVar12 ^ uVar17 ^ uVar9;
	uVar18 = uVar18 >> 0x1f | uVar18 << 1;
	uVar22 = uVar22 + (uVar19 >> 0x1b | uVar19 * 0x20) + ((uVar15 ^ uVar14) & uVar10 ^ uVar14) +
	         0x5a827999 + uVar18;
	uVar10 = uVar10 >> 2 | uVar10 * 0x40000000;
	uVar2 = uVar2 ^ uVar3 ^ uVar20 ^ uVar21;
	uVar2 = uVar2 >> 0x1f | uVar2 << 1;
	uVar14 = uVar14 + (uVar22 >> 0x1b | uVar22 * 0x20) + ((uVar10 ^ uVar15) & uVar19 ^ uVar15) +
	         0x5a827999 + uVar2;
	uVar19 = uVar19 >> 2 | uVar19 * 0x40000000;
	uVar12 = uVar12 ^ uVar4 ^ uVar6 ^ uVar1;
	uVar12 = uVar12 >> 0x1f | uVar12 << 1;
	uVar15 = uVar15 + (uVar14 >> 0x1b | uVar14 * 0x20) + (uVar22 ^ uVar19 ^ uVar10) + 0x6ed9eba1 +
	         uVar12;
	uVar3 = uVar3 ^ uVar5 ^ uVar7 ^ uVar18;
	uVar3 = uVar3 >> 0x1f | uVar3 << 1;
	uVar22 = uVar22 >> 2 | uVar22 * 0x40000000;
	uVar10 =
	    uVar10 + (uVar15 >> 0x1b | uVar15 * 0x20) + (uVar14 ^ uVar22 ^ uVar19) + 0x6ed9eba1 + uVar3;
	uVar14 = uVar14 >> 2 | uVar14 * 0x40000000;
	uVar4 = uVar4 ^ uVar13 ^ uVar8 ^ uVar2;
	uVar4 = uVar4 >> 0x1f | uVar4 << 1;
	uVar19 =
	    uVar19 + (uVar10 >> 0x1b | uVar10 * 0x20) + (uVar15 ^ uVar14 ^ uVar22) + 0x6ed9eba1 + uVar4;
	uVar15 = uVar15 >> 2 | uVar15 * 0x40000000;
	uVar5 = uVar5 ^ uVar11 ^ uVar9 ^ uVar12;
	uVar5 = uVar5 >> 0x1f | uVar5 << 1;
	uVar22 =
	    uVar22 + (uVar19 >> 0x1b | uVar19 * 0x20) + (uVar10 ^ uVar15 ^ uVar14) + 0x6ed9eba1 + uVar5;
	uVar10 = uVar10 >> 2 | uVar10 * 0x40000000;
	uVar13 = uVar13 ^ uVar17 ^ uVar21 ^ uVar3;
	uVar13 = uVar13 >> 0x1f | uVar13 << 1;
	uVar14 = uVar14 + (uVar22 >> 0x1b | uVar22 * 0x20) + (uVar19 ^ uVar10 ^ uVar15) + 0x6ed9eba1 +
	         uVar13;
	uVar19 = uVar19 >> 2 | uVar19 * 0x40000000;
	uVar11 = uVar11 ^ uVar20 ^ uVar1 ^ uVar4;
	uVar11 = uVar11 >> 0x1f | uVar11 << 1;
	uVar15 = uVar15 + (uVar14 >> 0x1b | uVar14 * 0x20) + (uVar22 ^ uVar19 ^ uVar10) + 0x6ed9eba1 +
	         uVar11;
	uVar17 = uVar17 ^ uVar6 ^ uVar18 ^ uVar5;
	uVar17 = uVar17 >> 0x1f | uVar17 << 1;
	uVar22 = uVar22 >> 2 | uVar22 * 0x40000000;
	uVar10 = uVar10 + (uVar15 >> 0x1b | uVar15 * 0x20) + (uVar14 ^ uVar22 ^ uVar19) + 0x6ed9eba1 +
	         uVar17;
	uVar14 = uVar14 >> 2 | uVar14 * 0x40000000;
	uVar20 = uVar20 ^ uVar7 ^ uVar2 ^ uVar13;
	uVar20 = uVar20 >> 0x1f | uVar20 << 1;
	uVar19 = uVar19 + (uVar10 >> 0x1b | uVar10 * 0x20) + (uVar15 ^ uVar14 ^ uVar22) + 0x6ed9eba1 +
	         uVar20;
	uVar15 = uVar15 >> 2 | uVar15 * 0x40000000;
	uVar6 = uVar6 ^ uVar8 ^ uVar12 ^ uVar11;
	uVar6 = uVar6 >> 0x1f | uVar6 << 1;
	uVar22 =
	    uVar22 + (uVar19 >> 0x1b | uVar19 * 0x20) + (uVar10 ^ uVar15 ^ uVar14) + 0x6ed9eba1 + uVar6;
	uVar10 = uVar10 >> 2 | uVar10 * 0x40000000;
	uVar7 = uVar7 ^ uVar9 ^ uVar3 ^ uVar17;
	uVar7 = uVar7 >> 0x1f | uVar7 << 1;
	uVar14 =
	    uVar14 + (uVar22 >> 0x1b | uVar22 * 0x20) + (uVar19 ^ uVar10 ^ uVar15) + 0x6ed9eba1 + uVar7;
	uVar19 = uVar19 >> 2 | uVar19 * 0x40000000;
	uVar8 = uVar8 ^ uVar21 ^ uVar4 ^ uVar20;
	uVar8 = uVar8 >> 0x1f | uVar8 << 1;
	uVar15 =
	    uVar15 + (uVar14 >> 0x1b | uVar14 * 0x20) + (uVar22 ^ uVar19 ^ uVar10) + 0x6ed9eba1 + uVar8;
	uVar9 = uVar9 ^ uVar1 ^ uVar5 ^ uVar6;
	uVar9 = uVar9 >> 0x1f | uVar9 << 1;
	uVar22 = uVar22 >> 2 | uVar22 * 0x40000000;
	uVar10 =
	    uVar10 + (uVar15 >> 0x1b | uVar15 * 0x20) + (uVar14 ^ uVar22 ^ uVar19) + 0x6ed9eba1 + uVar9;
	uVar14 = uVar14 >> 2 | uVar14 * 0x40000000;
	uVar21 = uVar21 ^ uVar18 ^ uVar13 ^ uVar7;
	uVar21 = uVar21 >> 0x1f | uVar21 << 1;
	uVar19 = uVar19 + (uVar10 >> 0x1b | uVar10 * 0x20) + (uVar15 ^ uVar14 ^ uVar22) + 0x6ed9eba1 +
	         uVar21;
	uVar15 = uVar15 >> 2 | uVar15 * 0x40000000;
	uVar1 = uVar1 ^ uVar2 ^ uVar11 ^ uVar8;
	uVar1 = uVar1 >> 0x1f | uVar1 << 1;
	uVar22 =
	    uVar22 + (uVar19 >> 0x1b | uVar19 * 0x20) + (uVar10 ^ uVar15 ^ uVar14) + 0x6ed9eba1 + uVar1;
	uVar10 = uVar10 >> 2 | uVar10 * 0x40000000;
	uVar18 = uVar18 ^ uVar12 ^ uVar17 ^ uVar9;
	uVar18 = uVar18 >> 0x1f | uVar18 << 1;
	uVar14 = uVar14 + (uVar22 >> 0x1b | uVar22 * 0x20) + (uVar19 ^ uVar10 ^ uVar15) + 0x6ed9eba1 +
	         uVar18;
	uVar19 = uVar19 >> 2 | uVar19 * 0x40000000;
	uVar2 = uVar2 ^ uVar3 ^ uVar20 ^ uVar21;
	uVar2 = uVar2 >> 0x1f | uVar2 << 1;
	uVar15 =
	    uVar15 + (uVar14 >> 0x1b | uVar14 * 0x20) + (uVar22 ^ uVar19 ^ uVar10) + 0x6ed9eba1 + uVar2;
	uVar12 = uVar12 ^ uVar4 ^ uVar6 ^ uVar1;
	uVar12 = uVar12 >> 0x1f | uVar12 << 1;
	uVar22 = uVar22 >> 2 | uVar22 * 0x40000000;
	uVar10 = uVar10 + (uVar15 >> 0x1b | uVar15 * 0x20) + (uVar14 ^ uVar22 ^ uVar19) + 0x6ed9eba1 +
	         uVar12;
	uVar14 = uVar14 >> 2 | uVar14 * 0x40000000;
	uVar3 = uVar3 ^ uVar5 ^ uVar7 ^ uVar18;
	uVar3 = uVar3 >> 0x1f | uVar3 << 1;
	uVar19 =
	    uVar19 + (uVar10 >> 0x1b | uVar10 * 0x20) + (uVar15 ^ uVar14 ^ uVar22) + 0x6ed9eba1 + uVar3;
	uVar15 = uVar15 >> 2 | uVar15 * 0x40000000;
	uVar4 = uVar4 ^ uVar13 ^ uVar8 ^ uVar2;
	uVar4 = uVar4 >> 0x1f | uVar4 << 1;
	uVar22 =
	    uVar22 + (uVar19 >> 0x1b | uVar19 * 0x20) + (uVar10 ^ uVar15 ^ uVar14) + 0x6ed9eba1 + uVar4;
	uVar10 = uVar10 >> 2 | uVar10 * 0x40000000;
	uVar5 = uVar5 ^ uVar11 ^ uVar9 ^ uVar12;
	uVar5 = uVar5 >> 0x1f | uVar5 << 1;
	uVar14 =
	    uVar14 + (uVar22 >> 0x1b | uVar22 * 0x20) + (uVar19 ^ uVar10 ^ uVar15) + 0x6ed9eba1 + uVar5;
	uVar19 = uVar19 >> 2 | uVar19 * 0x40000000;
	uVar13 = uVar13 ^ uVar17 ^ uVar21 ^ uVar3;
	uVar13 = uVar13 >> 0x1f | uVar13 << 1;
	uVar15 = uVar15 + (uVar14 >> 0x1b | uVar14 * 0x20) +
	         ((uVar22 | uVar19) & uVar10 | uVar22 & uVar19) + -0x70e44324 + uVar13;
	uVar22 = uVar22 >> 2 | uVar22 * 0x40000000;
	uVar11 = uVar11 ^ uVar20 ^ uVar1 ^ uVar4;
	uVar11 = uVar11 >> 0x1f | uVar11 << 1;
	uVar10 = uVar10 + (uVar15 >> 0x1b | uVar15 * 0x20) +
	         ((uVar14 | uVar22) & uVar19 | uVar14 & uVar22) + -0x70e44324 + uVar11;
	uVar14 = uVar14 >> 2 | uVar14 * 0x40000000;
	uVar17 = uVar17 ^ uVar6 ^ uVar18 ^ uVar5;
	uVar17 = uVar17 >> 0x1f | uVar17 << 1;
	uVar19 = uVar19 + (uVar10 >> 0x1b | uVar10 * 0x20) +
	         ((uVar15 | uVar14) & uVar22 | uVar15 & uVar14) + -0x70e44324 + uVar17;
	uVar15 = uVar15 >> 2 | uVar15 * 0x40000000;
	uVar20 = uVar20 ^ uVar7 ^ uVar2 ^ uVar13;
	uVar20 = uVar20 >> 0x1f | uVar20 << 1;
	uVar22 = uVar22 + (uVar19 >> 0x1b | uVar19 * 0x20) +
	         ((uVar10 | uVar15) & uVar14 | uVar10 & uVar15) + -0x70e44324 + uVar20;
	uVar10 = uVar10 >> 2 | uVar10 * 0x40000000;
	uVar6 = uVar6 ^ uVar8 ^ uVar12 ^ uVar11;
	uVar6 = uVar6 >> 0x1f | uVar6 << 1;
	uVar14 = uVar14 + (uVar22 >> 0x1b | uVar22 * 0x20) +
	         ((uVar19 | uVar10) & uVar15 | uVar19 & uVar10) + -0x70e44324 + uVar6;
	uVar19 = uVar19 >> 2 | uVar19 * 0x40000000;
	uVar7 = uVar7 ^ uVar9 ^ uVar3 ^ uVar17;
	uVar7 = uVar7 >> 0x1f | uVar7 << 1;
	uVar15 = uVar15 + (uVar14 >> 0x1b | uVar14 * 0x20) +
	         ((uVar22 | uVar19) & uVar10 | uVar22 & uVar19) + -0x70e44324 + uVar7;
	uVar22 = uVar22 >> 2 | uVar22 * 0x40000000;
	uVar8 = uVar8 ^ uVar21 ^ uVar4 ^ uVar20;
	uVar8 = uVar8 >> 0x1f | uVar8 << 1;
	uVar10 = uVar10 + (uVar15 >> 0x1b | uVar15 * 0x20) +
	         ((uVar14 | uVar22) & uVar19 | uVar14 & uVar22) + -0x70e44324 + uVar8;
	uVar14 = uVar14 >> 2 | uVar14 * 0x40000000;
	uVar9 = uVar9 ^ uVar1 ^ uVar5 ^ uVar6;
	uVar9 = uVar9 >> 0x1f | uVar9 << 1;
	uVar19 = uVar19 + (uVar10 >> 0x1b | uVar10 * 0x20) +
	         ((uVar15 | uVar14) & uVar22 | uVar15 & uVar14) + -0x70e44324 + uVar9;
	uVar15 = uVar15 >> 2 | uVar15 * 0x40000000;
	uVar21 = uVar21 ^ uVar18 ^ uVar13 ^ uVar7;
	uVar21 = uVar21 >> 0x1f | uVar21 << 1;
	uVar22 = uVar22 + (uVar19 >> 0x1b | uVar19 * 0x20) +
	         ((uVar10 | uVar15) & uVar14 | uVar10 & uVar15) + -0x70e44324 + uVar21;
	uVar10 = uVar10 >> 2 | uVar10 * 0x40000000;
	uVar1 = uVar1 ^ uVar2 ^ uVar11 ^ uVar8;
	uVar1 = uVar1 >> 0x1f | uVar1 << 1;
	uVar14 = uVar14 + (uVar22 >> 0x1b | uVar22 * 0x20) +
	         ((uVar19 | uVar10) & uVar15 | uVar19 & uVar10) + -0x70e44324 + uVar1;
	uVar19 = uVar19 >> 2 | uVar19 * 0x40000000;
	uVar18 = uVar18 ^ uVar12 ^ uVar17 ^ uVar9;
	uVar18 = uVar18 >> 0x1f | uVar18 << 1;
	uVar15 = uVar15 + (uVar14 >> 0x1b | uVar14 * 0x20) +
	         ((uVar22 | uVar19) & uVar10 | uVar22 & uVar19) + -0x70e44324 + uVar18;
	uVar22 = uVar22 >> 2 | uVar22 * 0x40000000;
	uVar2 = uVar2 ^ uVar3 ^ uVar20 ^ uVar21;
	uVar2 = uVar2 >> 0x1f | uVar2 << 1;
	uVar10 = uVar10 + (uVar15 >> 0x1b | uVar15 * 0x20) +
	         ((uVar14 | uVar22) & uVar19 | uVar14 & uVar22) + -0x70e44324 + uVar2;
	uVar14 = uVar14 >> 2 | uVar14 * 0x40000000;
	uVar12 = uVar12 ^ uVar4 ^ uVar6 ^ uVar1;
	uVar12 = uVar12 >> 0x1f | uVar12 << 1;
	uVar19 = uVar19 + (uVar10 >> 0x1b | uVar10 * 0x20) +
	         ((uVar15 | uVar14) & uVar22 | uVar15 & uVar14) + -0x70e44324 + uVar12;
	uVar15 = uVar15 >> 2 | uVar15 * 0x40000000;
	uVar3 = uVar3 ^ uVar5 ^ uVar7 ^ uVar18;
	uVar3 = uVar3 >> 0x1f | uVar3 << 1;
	uVar22 = uVar22 + (uVar19 >> 0x1b | uVar19 * 0x20) +
	         ((uVar10 | uVar15) & uVar14 | uVar10 & uVar15) + -0x70e44324 + uVar3;
	uVar10 = uVar10 >> 2 | uVar10 * 0x40000000;
	uVar4 = uVar4 ^ uVar13 ^ uVar8 ^ uVar2;
	uVar4 = uVar4 >> 0x1f | uVar4 << 1;
	uVar14 = uVar14 + (uVar22 >> 0x1b | uVar22 * 0x20) +
	         ((uVar19 | uVar10) & uVar15 | uVar19 & uVar10) + -0x70e44324 + uVar4;
	uVar19 = uVar19 >> 2 | uVar19 * 0x40000000;
	uVar5 = uVar5 ^ uVar11 ^ uVar9 ^ uVar12;
	uVar5 = uVar5 >> 0x1f | uVar5 << 1;
	uVar15 = uVar15 + (uVar14 >> 0x1b | uVar14 * 0x20) +
	         ((uVar22 | uVar19) & uVar10 | uVar22 & uVar19) + -0x70e44324 + uVar5;
	uVar22 = uVar22 >> 2 | uVar22 * 0x40000000;
	uVar13 = uVar13 ^ uVar17 ^ uVar21 ^ uVar3;
	uVar13 = uVar13 >> 0x1f | uVar13 << 1;
	uVar10 = uVar10 + (uVar15 >> 0x1b | uVar15 * 0x20) +
	         ((uVar14 | uVar22) & uVar19 | uVar14 & uVar22) + -0x70e44324 + uVar13;
	uVar14 = uVar14 >> 2 | uVar14 * 0x40000000;
	uVar11 = uVar11 ^ uVar20 ^ uVar1 ^ uVar4;
	uVar11 = uVar11 >> 0x1f | uVar11 << 1;
	uVar19 = uVar19 + (uVar10 >> 0x1b | uVar10 * 0x20) +
	         ((uVar15 | uVar14) & uVar22 | uVar15 & uVar14) + -0x70e44324 + uVar11;
	uVar15 = uVar15 >> 2 | uVar15 * 0x40000000;
	uVar17 = uVar17 ^ uVar6 ^ uVar18 ^ uVar5;
	uVar17 = uVar17 >> 0x1f | uVar17 << 1;
	uVar22 = uVar22 + (uVar19 >> 0x1b | uVar19 * 0x20) +
	         ((uVar10 | uVar15) & uVar14 | uVar10 & uVar15) + -0x70e44324 + uVar17;
	uVar10 = uVar10 >> 2 | uVar10 * 0x40000000;
	uVar20 = uVar20 ^ uVar7 ^ uVar2 ^ uVar13;
	uVar20 = uVar20 >> 0x1f | uVar20 << 1;
	uVar14 = uVar14 + (uVar22 >> 0x1b | uVar22 * 0x20) +
	         ((uVar19 | uVar10) & uVar15 | uVar19 & uVar10) + -0x70e44324 + uVar20;
	uVar16 = uVar19 >> 2 | uVar19 * 0x40000000;
	uVar6 = uVar6 ^ uVar8 ^ uVar12 ^ uVar11;
	uVar6 = uVar6 >> 0x1f | uVar6 << 1;
	uVar15 = uVar15 + (uVar14 >> 0x1b | uVar14 * 0x20) + (uVar22 ^ uVar16 ^ uVar10) + -0x359d3e2a +
	         uVar6;
	uVar19 = uVar22 >> 2 | uVar22 * 0x40000000;
	uVar7 = uVar7 ^ uVar9 ^ uVar3 ^ uVar17;
	uVar7 = uVar7 >> 0x1f | uVar7 << 1;
	uVar10 = uVar10 + (uVar15 >> 0x1b | uVar15 * 0x20) + (uVar14 ^ uVar19 ^ uVar16) + -0x359d3e2a +
	         uVar7;
	uVar22 = uVar14 >> 2 | uVar14 * 0x40000000;
	uVar8 = uVar8 ^ uVar21 ^ uVar4 ^ uVar20;
	uVar8 = uVar8 >> 0x1f | uVar8 << 1;
	uVar16 = uVar16 + (uVar10 >> 0x1b | uVar10 * 0x20) + (uVar15 ^ uVar22 ^ uVar19) + -0x359d3e2a +
	         uVar8;
	uVar15 = uVar15 >> 2 | uVar15 * 0x40000000;
	uVar9 = uVar9 ^ uVar1 ^ uVar5 ^ uVar6;
	uVar9 = uVar9 >> 0x1f | uVar9 << 1;
	uVar19 = uVar19 + (uVar16 >> 0x1b | uVar16 * 0x20) + (uVar10 ^ uVar15 ^ uVar22) + -0x359d3e2a +
	         uVar9;
	uVar10 = uVar10 >> 2 | uVar10 * 0x40000000;
	uVar21 = uVar21 ^ uVar18 ^ uVar13 ^ uVar7;
	uVar21 = uVar21 >> 0x1f | uVar21 << 1;
	uVar22 = uVar22 + (uVar19 >> 0x1b | uVar19 * 0x20) + (uVar16 ^ uVar10 ^ uVar15) + -0x359d3e2a +
	         uVar21;
	uVar1 = uVar1 ^ uVar2 ^ uVar11 ^ uVar8;
	uVar1 = uVar1 >> 0x1f | uVar1 << 1;
	uVar14 = uVar16 >> 2 | uVar16 * 0x40000000;
	uVar15 = uVar15 + (uVar22 >> 0x1b | uVar22 * 0x20) + (uVar19 ^ uVar14 ^ uVar10) + -0x359d3e2a +
	         uVar1;
	uVar18 = uVar18 ^ uVar12 ^ uVar17 ^ uVar9;
	uVar18 = uVar18 >> 0x1f | uVar18 << 1;
	uVar19 = uVar19 >> 2 | uVar19 * 0x40000000;
	uVar10 = uVar10 + (uVar15 >> 0x1b | uVar15 * 0x20) + (uVar22 ^ uVar19 ^ uVar14) + -0x359d3e2a +
	         uVar18;
	uVar2 = uVar2 ^ uVar3 ^ uVar20 ^ uVar21;
	uVar2 = uVar2 >> 0x1f | uVar2 << 1;
	uVar23 = uVar22 >> 2 | uVar22 * 0x40000000;
	uVar14 = uVar14 + (uVar10 >> 0x1b | uVar10 * 0x20) + (uVar15 ^ uVar23 ^ uVar19) + -0x359d3e2a +
	         uVar2;
	uVar15 = uVar15 >> 2 | uVar15 * 0x40000000;
	uVar12 = uVar12 ^ uVar4 ^ uVar6 ^ uVar1;
	uVar12 = uVar12 >> 0x1f | uVar12 << 1;
	uVar19 = uVar19 + (uVar14 >> 0x1b | uVar14 * 0x20) + (uVar10 ^ uVar15 ^ uVar23) + -0x359d3e2a +
	         uVar12;
	uVar10 = uVar10 >> 2 | uVar10 * 0x40000000;
	uVar3 = uVar3 ^ uVar5 ^ uVar7 ^ uVar18;
	uVar3 = uVar3 >> 0x1f | uVar3 << 1;
	uVar23 = uVar23 + (uVar19 >> 0x1b | uVar19 * 0x20) + (uVar14 ^ uVar10 ^ uVar15) + -0x359d3e2a +
	         uVar3;
	uVar4 = uVar4 ^ uVar13 ^ uVar8 ^ uVar2;
	uVar4 = uVar4 >> 0x1f | uVar4 << 1;
	uVar16 = uVar14 >> 2 | uVar14 * 0x40000000;
	uVar15 = uVar15 + (uVar23 >> 0x1b | uVar23 * 0x20) + (uVar19 ^ uVar16 ^ uVar10) + -0x359d3e2a +
	         uVar4;
	uVar5 = uVar5 ^ uVar11 ^ uVar9 ^ uVar12;
	uVar5 = uVar5 >> 0x1f | uVar5 << 1;
	uVar22 = uVar19 >> 2 | uVar19 * 0x40000000;
	uVar10 = uVar10 + (uVar15 >> 0x1b | uVar15 * 0x20) + (uVar23 ^ uVar22 ^ uVar16) + -0x359d3e2a +
	         uVar5;
	uVar19 = uVar23 >> 2 | uVar23 * 0x40000000;
	uVar13 = uVar13 ^ uVar17 ^ uVar21 ^ uVar3;
	uVar14 = uVar13 >> 0x1f | uVar13 << 1;
	uVar16 = uVar16 + (uVar10 >> 0x1b | uVar10 * 0x20) + (uVar15 ^ uVar19 ^ uVar22) + -0x359d3e2a +
	         uVar14;
	uVar15 = uVar15 >> 2 | uVar15 * 0x40000000;
	uVar13 = uVar11 ^ uVar20 ^ uVar1 ^ uVar4;
	uVar13 = uVar13 >> 0x1f | uVar13 << 1;
	uVar22 = uVar22 + (uVar16 >> 0x1b | uVar16 * 0x20) + (uVar10 ^ uVar15 ^ uVar19) + -0x359d3e2a +
	         uVar13;
	uVar11 = uVar10 >> 2 | uVar10 * 0x40000000;
	uVar18 = uVar17 ^ uVar6 ^ uVar18 ^ uVar5;
	uVar18 = uVar18 >> 0x1f | uVar18 << 1;
	uVar19 = uVar19 + (uVar22 >> 0x1b | uVar22 * 0x20) + (uVar16 ^ uVar11 ^ uVar15) + -0x359d3e2a +
	         uVar18;
	uVar14 = uVar20 ^ uVar7 ^ uVar2 ^ uVar14;
	uVar2 = uVar14 >> 0x1f | uVar14 << 1;
	uVar20 = uVar16 >> 2 | uVar16 * 0x40000000;
	uVar15 = uVar15 + (uVar19 >> 0x1b | uVar19 * 0x20) + (uVar22 ^ uVar20 ^ uVar11) + -0x359d3e2a +
	         uVar2;
	uVar17 = uVar22 >> 2 | uVar22 * 0x40000000;
	uVar13 = uVar6 ^ uVar8 ^ uVar12 ^ uVar13;
	uVar12 = uVar13 >> 0x1f | uVar13 << 1;
	uVar11 = uVar11 + (uVar15 >> 0x1b | uVar15 * 0x20) + (uVar19 ^ uVar17 ^ uVar20) + -0x359d3e2a +
	         uVar12;
	uVar13 = uVar19 >> 2 | uVar19 * 0x40000000;
	uVar18 = uVar7 ^ uVar9 ^ uVar3 ^ uVar18;
	uVar20 = uVar20 + (uVar18 >> 0x1f | uVar18 << 1) + (uVar11 >> 0x1b | uVar11 * 0x20) +
	         (uVar15 ^ uVar13 ^ uVar17) + -0x359d3e2a;
	uVar18 = uVar15 >> 2 | uVar15 * 0x40000000;
	uVar2 = uVar8 ^ uVar21 ^ uVar4 ^ uVar2;
	uVar17 = uVar17 + (uVar2 >> 0x1f | uVar2 << 1) + (uVar20 >> 0x1b | uVar20 * 0x20) +
	         (uVar11 ^ uVar18 ^ uVar13) + -0x359d3e2a;
	uVar21 = uVar11 >> 2 | uVar11 * 0x40000000;
	uVar12 = uVar9 ^ uVar1 ^ uVar5 ^ uVar12;
	mState[0] = mState[0] + uVar13 + (uVar12 >> 0x1f | uVar12 << 1) +
	            (uVar17 >> 0x1b | uVar17 * 0x20) + (uVar20 ^ uVar21 ^ uVar18) + -0x359d3e2a;
	mState[1] = mState[1] + uVar17;
	mState[2] = mState[2] + (uVar20 >> 2 | uVar20 * 0x40000000);
	mState[3] = mState[3] + uVar21;
	mState[4] = mState[4] + uVar18;
	return;
}

// KDXClient.lexe: 080de748
void __cdecl _MD5::Update(const void *inData, uint inDataSize)
{
	int iVar1;
	uint uVar2;

	if (mBufferLength == 0x40)
	{
		Transform((const uint *)mBuffer);
		mBufferLength = 0;
		mCount = mCount + 1;
	}
	if (inData != NULL)
	{
		if (mBufferLength != 0)
		{
			while ((inDataSize != 0 && (mBufferLength < 0x40)))
			{
				iVar1 = mBufferLength;
				mBufferLength = mBufferLength + 1;
				uVar2 = *(const uint *)inData;
				inData = (const void *)((ulonglong)inData + 1);
				mBuffer[iVar1] = (uchar)uVar2;
				inDataSize = inDataSize - 1;
			}
			if (mBufferLength == 0x40)
			{
				Transform((const uint *)mBuffer);
				mBufferLength = 0;
				mCount = mCount + 1;
			}
			if (inDataSize == 0)
			{
				return;
			}
		}
		for (; 0x3f < inDataSize; inDataSize = inDataSize - 0x40)
		{
			Transform((const uint *)inData);
			mBufferLength = 0;
			mCount = mCount + 1;
			inData = (const void *)((ulonglong)inData + 0x40);
		}
		while ((inDataSize != 0 && (mBufferLength < 0x40)))
		{
			iVar1 = mBufferLength;
			mBufferLength = mBufferLength + 1;
			uVar2 = *(const uint *)inData;
			inData = (void *)((ulonglong)inData + 1);
			mBuffer[iVar1] = (uchar)uVar2;
			inDataSize = inDataSize - 1;
		}
		return;
	}
	return;
}
