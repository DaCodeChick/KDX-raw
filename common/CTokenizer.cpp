#include "CTokenizer.h"

// KDXServer.exe: 00434b20
CTokenizer::CTokenizer(void *inOffset, uint inSize, const void *inDelimiters, uint inOptions)
{
	byte *pbVar1;
	byte bVar2;
	uint uVar3;
	uint local_14;

	mOffset = (byte *)inOffset;
	mEnd = (byte *)((ulonglong)inOffset + inSize);
	mFlags = inOptions;
	mPos = 0;
	mDelimiterBits[0] = 0;
	mDelimiterBits[1] = 0;
	mDelimiterBits[2] = 0;
	mDelimiterBits[3] = 0;
	mDelimiterBits[4] = 0;
	mDelimiterBits[5] = 0;
	mDelimiterBits[6] = 0;
	if (inDelimiters == NULL)
	{
		local_14 = 0;
	}
	else
	{
		local_14 = (uint) * (byte *)inDelimiters;
	}
	uVar3 = 1;
	if (local_14 != 0)
	{
		if (8 < local_14)
		{
			do
			{
				pbVar1 = (byte *)((ulonglong)mDelimiterBits +
				                  ((*(byte *)((ulonglong)inDelimiters + uVar3) >> 3) - 4));
				*pbVar1 = *pbVar1 | '\x01' << (*(byte *)((ulonglong)inDelimiters + uVar3) & 7);
				bVar2 = *(byte *)((ulonglong)inDelimiters + uVar3 + 1);
				pbVar1 = (byte *)((ulonglong)mDelimiterBits + ((bVar2 >> 3) - 4));
				*pbVar1 = *pbVar1 | '\x01' << (bVar2 & 7);
				bVar2 = *(byte *)((ulonglong)inDelimiters + uVar3 + 2);
				pbVar1 = (byte *)((ulonglong)mDelimiterBits + ((bVar2 >> 3) - 4));
				*pbVar1 = *pbVar1 | '\x01' << (bVar2 & 7);
				bVar2 = *(byte *)((ulonglong)inDelimiters + uVar3 + 3);
				pbVar1 = (byte *)((ulonglong)mDelimiterBits + ((bVar2 >> 3) - 4));
				*pbVar1 = *pbVar1 | '\x01' << (bVar2 & 7);
				bVar2 = *(byte *)((ulonglong)inDelimiters + uVar3 + 4);
				pbVar1 = (byte *)((ulonglong)mDelimiterBits + ((bVar2 >> 3) - 4));
				*pbVar1 = *pbVar1 | '\x01' << (bVar2 & 7);
				bVar2 = *(byte *)((ulonglong)inDelimiters + uVar3 + 5);
				pbVar1 = (byte *)((ulonglong)mDelimiterBits + ((bVar2 >> 3) - 4));
				*pbVar1 = *pbVar1 | '\x01' << (bVar2 & 7);
				bVar2 = *(byte *)((ulonglong)inDelimiters + uVar3 + 6);
				pbVar1 = (byte *)((ulonglong)mDelimiterBits + ((bVar2 >> 3) - 4));
				*pbVar1 = *pbVar1 | '\x01' << (bVar2 & 7);
				bVar2 = *(byte *)((ulonglong)inDelimiters + uVar3 + 7);
				uVar3 = uVar3 + 8;
				pbVar1 = (byte *)((ulonglong)mDelimiterBits + ((bVar2 >> 3) - 4));
				*pbVar1 = *pbVar1 | '\x01' << (bVar2 & 7);
			} while (uVar3 <= local_14 - 8);
		}
		for (; uVar3 <= local_14; uVar3 = uVar3 + 1)
		{
			pbVar1 = (byte *)((ulonglong)mDelimiterBits +
			                  ((*(byte *)((ulonglong)inDelimiters + uVar3) >> 3) - 4));
			*pbVar1 = *pbVar1 | '\x01' << (*(byte *)((ulonglong)inDelimiters + uVar3) & 7);
		}
	}
	if ((inOptions & 1) == 0)
	{
		mGetNextTokenProc = GetNextTokenDefault;
	}
	else if ((inOptions & 2) == 0)
	{
		mGetNextTokenProc = GetNextTokenWithDelimiters;
	}
	else
	{
		mGetNextTokenProc = GetNextTokenTrimWhitespace;
	}
}

// KDXServer.exe: 00434b00
void *CTokenizer::GetNextToken(uint *outSize, void *outDelimiter)
{
	(this->*mGetNextTokenProc)(outSize, outDelimiter);
	return;
}

// KDXServer.exe: 00434a30
void *CTokenizer::GetNextTokenDefault(uint *outSize, void *outDelimiter)
{
	byte bVar1;
	byte *pbVar2;
	byte *local_14;

	local_14 = mOffset;
	pbVar2 = local_14;
	if ((local_14 < mEnd) &&
	    (bVar1 = *local_14, (1 << (bVar1 & 7) & (uint) * (byte *)((ulonglong)mDelimiterBits +
	                                                              ((bVar1 >> 3) - 4))) != 0))
	{
		if (outDelimiter != NULL)
		{
			*(byte *)outDelimiter = bVar1;
		}
		if (outSize != NULL)
		{
			*outSize = 1;
		}
		mOffset = local_14 + 1;
		return local_14;
	}
	while ((pbVar2 < mEnd && ((1 << (*pbVar2 & 7) & (uint) * (byte *)((ulonglong)mDelimiterBits +
	                                                                  ((*pbVar2 >> 3) - 4))) == 0)))
	{
		pbVar2 = pbVar2 + 1;
	}
	if (outSize != NULL)
	{
		*outSize = (ulonglong)pbVar2 - (ulonglong)local_14;
	}
	if (outDelimiter != NULL)
	{
		*(undefined1 *)outDelimiter = 0;
	}
	mOffset = pbVar2;
	if ((ulonglong)pbVar2 - (ulonglong)local_14 == 0)
	{
		local_14 = NULL;
	}
	return local_14;
}

// KDXServer.exe: 00434990
void *CTokenizer::GetNextTokenWithDelimiters(uint *outSize, void *outDelimiter)
{
	byte *pbVar1;
	byte *pbVar2;

	pbVar2 = mOffset;
	while ((pbVar1 = pbVar2,
	        pbVar2 < mEnd && ((1 << (*pbVar2 & 7) & (uint) * (byte *)((ulonglong)mDelimiterBits +
	                                                                  ((*pbVar2 >> 3) - 4))) != 0)))
	{
		pbVar2 = pbVar2 + 1;
	}
	while ((pbVar1 < mEnd && ((1 << (*pbVar1 & 7) & (uint) * (byte *)((ulonglong)mDelimiterBits +
	                                                                  ((*pbVar1 >> 3) - 4))) == 0)))
	{
		pbVar1 = pbVar1 + 1;
	}
	if (outSize != NULL)
	{
		*outSize = (ulonglong)pbVar1 - (ulonglong)pbVar2;
	}
	if (outDelimiter != NULL)
	{
		*(byte *)outDelimiter = 0;
	}
	mOffset = pbVar1;
	if ((ulonglong)pbVar1 - (ulonglong)pbVar2 == 0)
	{
		pbVar2 = NULL;
	}
	return pbVar2;
}

// KDXServer.exe: 004348e0
void *CTokenizer::GetNextTokenTrimWhitespace(uint *outSize, void *outDelimiter)
{
	byte bVar1;
	byte *pbVar2;
	byte *pbVar3;
	byte *pbVar4;

	if (outDelimiter != NULL)
	{
		*(byte *)outDelimiter = 0;
	}
	pbVar2 = mOffset;
	pbVar3 = mEnd;
	pbVar4 = pbVar2;
	if (pbVar3 <= pbVar2)
	{
		if (outSize != NULL)
		{
			*outSize = 0;
		}
		return NULL;
	}
	do
	{
		bVar1 = *pbVar4;
		pbVar4 = pbVar4 + 1;
		if ((1 << (bVar1 & 7) &
		     (uint) * (byte *)((ulonglong)mDelimiterBits + ((bVar1 >> 3) - 4))) != 0)
		{
			if (outSize != NULL)
			{
				*outSize = (ulonglong)(pbVar4 + (-1 - (ulonglong)pbVar2));
			}
			mOffset = pbVar4;
			return pbVar2;
		}
	} while (pbVar4 < pbVar3);
	if (outSize != NULL)
	{
		*outSize = (ulonglong)pbVar3 - (ulonglong)pbVar2;
	}
	mOffset = pbVar3;
	return pbVar2;
}
