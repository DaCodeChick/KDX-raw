#pragma once

#include "typedefs.h"

class EXPORT CTwofish
{
public:
	CTwofish(const void *inData);
	void Encrypt(const void *inData, void *outData);
	void EncryptCBC(void *outData, uint *ioPartialBlockSize, const void *inData, uint inDataSize);

private:
	uint mSBox[4][256];
	uint mKey[40];

	void EncryptCBCIteration(const void *inData, void *outData);
};