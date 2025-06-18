#include "UGraphics.h"

// AppearanceEdit.exe: 00403650
uint UGraphics::AdjustColorWithBleed(uint inColor, int inFactor)
{
	uint uVar1;
	uint uVar2;
	uint uVar3;
	uint uVar4;
	uint uVar5;
	uint uVar6;

	uVar3 = (inColor >> 8 & 0xff) + inFactor;
	uVar1 = (inColor >> 0x10 & 0xff) + inFactor;
	uVar2 = (inColor >> 0x18) + inFactor;
	if (uVar3 < 0x100)
	{
		uVar6 = 0;
	}
	else
	{
		uVar6 = uVar3 - 0xff >> 1;
	}
	if (uVar1 < 0x100)
	{
		uVar5 = 0;
	}
	else
	{
		uVar5 = uVar1 - 0xff >> 1;
	}
	if (uVar2 < 0x100)
	{
		uVar4 = 0;
	}
	else
	{
		uVar4 = uVar2 - 0xff >> 1;
	}
	uVar3 = uVar3 + uVar5 + uVar4;
	uVar5 = uVar2 + uVar6 + uVar5;
	uVar4 = uVar1 + uVar6 + uVar4;
	if (0xff < uVar3)
	{
		uVar3 = 0xff;
	}
	if (0xff < uVar4)
	{
		uVar4 = 0xff;
	}
	if (0xff < uVar5)
	{
		uVar5 = 0xff;
	}
	return (uVar4 & 0xff) << 0x10 | (uVar3 & 0xff) << 8 | uVar5 << 0x18;
}

// AppearanceEdit.exe: 004037d0
uint UGraphics::BlendColorChannels(uint inColor, int inFactor)
{
	uint uVar1;
	uint uVar2;
	undefined4 local_14;

	local_14 = inColor >> 8 & 0xff;
	if (local_14 != 0)
	{
		local_14 = 0xff - ((0xff - local_14) * inFactor) / 0xff;
	}
	uVar2 = inColor >> 0x10 & 0xff;
	if (uVar2 != 0)
	{
		uVar2 = 0xff - ((0xff - uVar2) * inFactor) / 0xff;
	}
	uVar1 = inColor >> 0x18;
	if (uVar1 != 0)
	{
		uVar1 = 0xff - ((0xff - uVar1) * inFactor) / 0xff;
	}
	return (uVar2 & 0xff) << 0x10 | (local_14 & 0xff) << 8 | uVar1 << 0x18;
}

// AppearanceEdit.exe: 00403710
uint UGraphics::ReduceColorWithBleed(uint inColor, int inFactor)
{
	int iVar1;
	uint uVar2;
	int iVar3;
	int iVar4;
	uint uVar5;
	int iVar6;
	int iVar7;
	int iVar8;

	iVar4 = (inColor >> 8 & 0xff) - inFactor;
	iVar1 = (inColor >> 0x10 & 0xff) - inFactor;
	iVar3 = (inColor >> 0x18) - inFactor;
	if (iVar4 < 0)
	{
		iVar8 = (int)((-iVar4 + 1U) - (uint)((uint)-iVar4 < 0x80000000)) >> 1;
	}
	else
	{
		iVar8 = 0;
	}
	if (iVar1 < 0)
	{
		iVar7 = (int)((-iVar1 + 1U) - (uint)((uint)-iVar1 < 0x80000000)) >> 1;
	}
	else
	{
		iVar7 = 0;
	}
	if (iVar3 < 0)
	{
		iVar6 = (int)((-iVar3 + 1U) - (uint)((uint)-iVar3 < 0x80000000)) >> 1;
	}
	else
	{
		iVar6 = 0;
	}
	uVar5 = (iVar4 - iVar7) - iVar6;
	iVar7 = (iVar3 - iVar8) - iVar7;
	uVar2 = (iVar1 - iVar8) - iVar6;
	if ((int)uVar5 < 0)
	{
		uVar5 = 0;
	}
	if ((int)uVar2 < 0)
	{
		uVar2 = 0;
	}
	if (iVar7 < 0)
	{
		iVar7 = 0;
	}
	return (uVar2 & 0xff) << 0x10 | (uVar5 & 0xff) << 8 | iVar7 << 0x18;
}

// AppearanceEdit.exe: 00403890
uint UGraphics::ScaleColorChannels(uint inColor, int inFactor)
{
	return (((inColor >> 0x10 & 0xff) * inFactor) / 0xff & 0xff) << 0x10 |
	       (((inColor >> 8 & 0xff) * inFactor) / 0xff & 0xff) << 8 |
	       ((inColor >> 0x18) * inFactor) / 0xff << 0x18;
}
