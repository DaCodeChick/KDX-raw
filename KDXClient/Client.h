#pragma once

#include "../common/typedefs.h"

void BlockCrypt1B20E200(void *ioData, bool inIsDecrypt);
void UDPPacketCrypt(void *outData, const void *inData, uint inDataSize);
