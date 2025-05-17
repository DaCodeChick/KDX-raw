#pragma once

#include "typedefs.h"

#ifdef _WIN32
typedef HGLOBAL THdl;
#else
#include <cstdlib>
typedef class THdlObj *THdl;
#endif // _WIN32

class EXPORT UMemory
{
public:
	static uint AdlerSum(const void *inData, uint inDataSize, uint inInit);
	static uint Checksum(const void *inData, uint inDataSize, uint inInit);
	static void Clear(void *outDest, uint inSize);
	static bool Compare(const void *inDataA, const void *inDataB, uint inSize);
	static uint CRC(const void *inData, uint inDataSize, uint inInit);
	static void Dispose(THdl inHdl);
	static void Fill(void *outDest, uint inSize, byte inByte);
	static void Fill(void *outDest, uint inSize, ushort inWord);
	static void Fill(void *outDest, uint inSize, uint inLong);
	static longlong GetHandleCount(uint *outCount);
	static void *Lock(THdl inHdl)
	{
#ifdef _WIN32
		return GlobalLock(inHdl);
#else
		return *inHdl;
#endif // _WIN32
	}
	static uint Move(void *outDest, const void *inSrc, uint inSize);
	static THdl NewHandle(uint inSize);
	static THdl NewHandle(const void *inData, uint inSize);
	static THdl NewHandleClear(uint inSize);
	static THdl Reallocate(THdl inHdl, uint inSize);
	static void *Search(const void *inSearchData, uint inSearchSize, const void *inData,
	                    uint inDataSize);
	static byte *SearchByte(byte inByte, const void *inData, uint inSize);
	static byte *SearchByteBackwards(byte inByte, const void *inData, uint inSize);
	static void Unlock(THdl inHdl)
	{
#ifdef _WIN32
		GlobalUnlock(inHdl);
#endif // _WIN32
	}
};

class EXPORT StHandleLocker
{
public:
	StHandleLocker(THdl inHdl, void *& outPtr):
		mHdl(inHdl)
	{
		outPtr = UMemory::Lock(mHdl);
	}

	~StHandleLocker()
	{
		UMemory::Unlock(mHdl);
	}
private:
	THdl mHdl;
};

#ifndef _WIN32
class THdlObj
{
public:
	THdlObj(uint inSize):
		mHdl(std::malloc(inSize)),
		mSize(inSize)
	{
	}
	
	THdlObj(const void *inData, uint inSize):
		mHdl(std::malloc(inSize)),
		mSize(inSize)
	{
		if (mHdl)
			UMemory::Move(mHdl, inData, inSize);
	}

	~THdlObj()
	{
		std::free(mHdl);
	}

	operator*()
	{
		return mHdl;
	}
private:
	void *mHdl;
	uint mSize;
};
#endif // _WIN32
