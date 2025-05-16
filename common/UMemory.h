#pragma once

#include "typedefs.h"

#ifdef _WIN32
typedef HGLOBAL TPtr;
#else
typedef void *TPtr;
#endif

class EXPORT UMemory
{
public:
	static uint Checksum(const void *inData, uint inDataSize, uint inInit);
	static void Clear(void *outDest, uint inSize);
	static bool Compare(const void *inDataA, const void *inDataB, uint inSize);
	static uint CRC(const void *inData, uint inDataSize, uint inInit);
	static void Dispose(TPtr inPtr);
	static void Fill(void *outDest, uint inSize, byte inByte);
	static void Fill(void *outDest, uint inSize, ushort inWord);
	static void Fill(void *outDest, uint inSize, uint inLong);
	static uint Move(void *outDest, const void *inSrc, uint inSize);
	static TPtr New(uint inSize);
	static TPtr New(const void *inData, uint inSize);
	static TPtr NewClear(uint inSize);
	static TPtr Reallocate(TPtr inPtr, uint inSize);
	static void *Search(const void *inSearchData, uint inSearchSize, const void *inData,
	                    uint inDataSize);
	static byte *SearchByte(byte inByte, const void *inData, uint inSize);
	static byte *SearchByteBackwards(byte inByte, const void *inData, uint inSize);
};
