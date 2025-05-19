#pragma once

#include "../common/typedefs.h"

void BlockCrypt1B20E200(void *ioData, bool inIsDecrypt);
void CertificateCrypt(const void *inData, void *outData);
void SettingsCrypt(void *ioData, uint inDataSize);
void UDPPacketCrypt(void *outData, const void *inData, uint inDataSize);
