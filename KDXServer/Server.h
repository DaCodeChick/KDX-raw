#pragma once

#include "../common/CPtrList.h"

struct BanRecord
{
	longlong expires;
	undefined2 field2_0x8;
	byte *address;
	byte *field4_0x10;
	byte *reason;
};

class CMyApplication
{
public:
	bool CheckIfBanned(const void *inAddr, uint inAddrSize);

private:
	CPtrList<BanRecord> mBans;
};

void AccountsDBCrypt(void *ioData, uint inDataSize);
void CryptA5A16C4A(void *outData, const void *inData, uint inDataSize);
