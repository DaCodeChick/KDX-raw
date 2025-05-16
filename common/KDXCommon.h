#pragma once

#include "CTwofish.h"
#include "UCryptTransact.h"
#include "URegularTransport.h"

struct SMyClient
{
	uint tag;
	uint magic;
	TCryptProc cryptProc;
	SRegularTransport *tpt;
	uint field4_0x10;
	void *field5_0x14;
	uint field6_0x18;
	uint field7_0x1c;
	uint field8_0x20;
	int field9_0x24;
	byte login[32];
	byte password[32];
	ulonglong sessionID;
	uint state;
	uint field14_0x74;
	uint key;
	int field16_0x7c;
	undefined *field17_0x80;
	int field18_0x84;
	undefined *field19_0x88;
	int field20_0x8c;
	uint *field21_0x90;
	uint field22_0x94;
	bool field23_0x98;
	byte field24_0x99;
	byte field25_0x9a;
	byte packetDataSize;
	ushort field27_0x9c;
	ushort drmOffset;
	ushort drmSize;
	undefined field30_0xa2;
	undefined field31_0xa3;
	byte *drm;
	int field33_0xa8;
	void *field34_0xac;
	void *field35_0xb0;
	void *field36_0xb4;
	void *field37_0xb8;
	byte iv[32];
	CTwofish twofishContext;
};

struct STCPPacketHeader
{
	uint key;
	uint txp;
	uint tag;
	byte field3_0xc;
	byte drmOffset;
	byte field5_0xe;
	byte dataSize;
	uint field7_0x10;
	ushort field8_0x14;
	ushort field9_0x16;
	uint field10_0x18;
	uint field11_0x1c;
	uint field12_0x20;
	uint field13_0x24;
};
