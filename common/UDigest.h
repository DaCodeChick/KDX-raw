#pragma once

#include "typedefs.h"

class EXPORT UDigest
{
public:
	static void *Base80_Decode(const void *inData, uint inDataSize, uint *outSize);
	static void MD5_Encode(const void *inData, uint inDataSize, void *outDigest);
};

class EXPORT _MD5
{
public:
	void Clear(uint inSize);
	void Init();
	void Report(void *outDigest);
	void Update(const void *inData, uint inDataSize);

private:
	uint mState[5];
	uint mCount;
	byte mBuffer[64];
	uint mBufferLength;

	void Transform(const uint *inBlock);
};
