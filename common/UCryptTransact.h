#pragma once

#include "typedefs.h"

typedef void (*TCryptProc)(void *ioData, bool isDecrypt);

class EXPORT UCryptTransact
{
public:
	static void BlockCrypt6E7DFD34(void *ioData, bool inIsDecrypt);
	static void GenerateKey(const void *inData, uint inDataSize, void *outData);
	static bool IsDefaultKey(const void *inData);
	static void TCPPacketCrypt(uint inInit, void *ioData, uint inDataSize);
};
