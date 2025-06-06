#include "UKeyboard.h"
#include "UMemory.h"
#include "UText.h"

// AppearanceEdit.exe: 00461150
static const byte gKCToWin[0x100] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x0c, 0x00, 0x6f, 0x6a, 0x6d, 0xbb,
    0x00, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
    0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xbd, 0x00, 0xdb, 0xdd, 0xdc, 0xba, 0xde, 0xbc, 0xbe, 0xbf, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x09, 0x0d, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x24, 0x23, 0x21, 0x22, 0x26, 0x28, 0x25, 0x27, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x1b, 0x08, 0x2f, 0x2e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x14, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0x5b, 0x5c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f,
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

// AppearanceEdit.exe: 004308b0
uint UKeyboard::KeyToChar(ushort inKeyCode, uint inMods)
{
	int iVar1;
	uint uVar2;
	uint uVar3;
	WCHAR local_11c;
	ushort local_11a;
	BYTE local_10c[16];
	undefined1 local_fc;
	undefined1 local_fb;
	undefined1 local_fa;
	undefined1 local_f8;
	undefined1 local_b1;

	uVar2 = (uint)gKCToWin[inKeyCode];
	if (inMods == 0)
	{
		uVar2 = MapVirtualKeyW(uVar2, 2);
		if ((uVar2 & 0x80000000) != 0)
		{
			uVar2 = 0;
		}
		uVar2 = UText::ToLower(uVar2);
		return uVar2;
	}
	if (inMods == 8)
	{
		uVar2 = MapVirtualKeyW(uVar2, 2);
		if ((uVar2 & 0x80000000) != 0)
		{
			uVar2 = 0;
		}
		uVar2 = UText::ToUpper(uVar2);
		return uVar2;
	}
	UMemory::Clear(local_10c, 0x100);
	if ((inMods & 0x21) != 0)
	{
		local_fb = 0x80;
	}
	if ((inMods & 2) != 0)
	{
		local_fa = 0x80;
	}
	if ((inMods & 8) != 0)
	{
		local_fc = 0x80;
	}
	if ((inMods & 4) != 0)
	{
		local_f8 = 0x80;
	}
	if ((inMods & 0x10) != 0)
	{
		local_b1 = 0x80;
	}
	uVar3 = 0;
	iVar1 = ToUnicode(uVar2, 0, local_10c, &local_11c, 7, 0);
	if (0 < iVar1)
	{
		if (((iVar1 == 2) && ((int)(uint)(ushort)local_11c >> 10 == 0x36)) &&
		    ((int)(uint)local_11a >> 10 == 0x37))
		{
			uVar3 = (((ushort)local_11c & 0x3ff) << 10 | local_11a & 0x3ff) + 0x10000;
		}
		else
		{
			uVar3 = (uint)(ushort)local_11c;
		}
	}
	return uVar3;
}
