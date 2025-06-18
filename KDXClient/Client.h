#pragma once

#include "../AppWarrior/typedefs.h"

void BlockCrypt1B20E200(void *ioData, bool inIsDecrypt);
void CryptE4FDBAA9(void *outData, const void *inData, uint inDataSize);
void CertificateCrypt(const void *inData, void *outData);
void SettingsCrypt(void *ioData, uint inDataSize);