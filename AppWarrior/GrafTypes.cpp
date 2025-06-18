#include "GrafTypes.h"

// KDXClient.exe: 004a3500
void SRect::Align(const SRect *inSourceRect, uint inOptions, const SRect *inRefRect)
{
	int iVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	uint uVar5;
	int iVar6;

	iVar1 = inSourceRect->left;
	iVar4 = inSourceRect->right;
	iVar3 = iVar4 - iVar1;
	if ((inOptions & 1) == 0)
	{
		if ((inOptions & 4) != 0)
		{
			iVar4 = inRefRect->right;
			left = iVar4 - iVar3;
			right = iVar4;
			goto LAB_004a35bf;
		}
		if ((inOptions & 0x10) == 0)
		{
			if ((inOptions & 0x40) == 0)
			{
				left = iVar1;
			}
			else
			{
				iVar2 = inRefRect->left;
				if (iVar1 < iVar2)
				{
					left = iVar2;
					iVar4 = iVar3 + iVar2;
				}
				else
				{
					iVar6 = inRefRect->right;
					if (iVar6 < iVar4)
					{
						iVar4 = iVar6 - iVar3;
						if (iVar6 - iVar3 < iVar2)
						{
							iVar6 = iVar3 + iVar2;
							iVar4 = iVar2;
						}
						left = iVar4;
						right = iVar6;
						goto LAB_004a35bf;
					}
					left = iVar1;
				}
			}
		}
		else
		{
			uVar5 = (inRefRect->left + inRefRect->right) - iVar3;
			iVar4 = (int)((uVar5 + 1) - (uint)(uVar5 < 0x80000000)) >> 1;
			left = iVar4;
			iVar4 = iVar4 + iVar3;
		}
	}
	else
	{
		iVar4 = inRefRect->left;
		left = iVar4;
		iVar4 = iVar4 + iVar3;
	}
	right = iVar4;
LAB_004a35bf:
	iVar4 = inSourceRect->bottom;
	iVar1 = inSourceRect->top;
	iVar3 = iVar4 - iVar1;
	if ((inOptions & 2) == 0)
	{
		if ((inOptions & 8) == 0)
		{
			if ((inOptions & 0x20) == 0)
			{
				if ((inOptions & 0x80) != 0)
				{
					iVar2 = inRefRect->top;
					if (iVar1 < iVar2)
					{
						top = iVar2;
						bottom = iVar3 + iVar2;
						return;
					}
					iVar6 = inRefRect->bottom;
					if (iVar6 < iVar4)
					{
						iVar4 = iVar6 - iVar3;
						if (iVar6 - iVar3 < iVar2)
						{
							iVar6 = iVar3 + iVar2;
							iVar4 = iVar2;
						}
						top = iVar4;
						bottom = iVar6;
						return;
					}
				}
				top = iVar1;
				bottom = iVar4;
			}
			else
			{
				uVar5 = (inRefRect->top + inRefRect->bottom) - iVar3;
				iVar4 = (int)((uVar5 + 1) - (uint)(uVar5 < 0x80000000)) >> 1;
				top = iVar4;
				bottom = iVar4 + iVar3;
			}
		}
		else
		{
			iVar4 = inRefRect->bottom;
			top = iVar4 - iVar3;
			bottom = iVar4;
		}
	}
	else
	{
		iVar4 = inRefRect->top;
		top = iVar4;
		bottom = iVar4 + iVar3;
	}
	return;
}

// KDXClient.exe: 004a3480
void SRect::Center(const SRect *inBase, const SRect *inContainer)
{
	uint uVar1;
	int iVar2;
	int iVar3;

	iVar3 = inBase->right - inBase->left;
	uVar1 = (inContainer->left + inContainer->right) - iVar3;
	iVar2 = (int)((uVar1 + 1) - (uint)(uVar1 < 0x80000000)) >> 1;
	left = iVar2;
	right = iVar2 + iVar3;
	iVar3 = inBase->bottom - inBase->top;
	uVar1 = (inContainer->top + inContainer->bottom) - iVar3;
	iVar2 = (int)((uVar1 + 1) - (uint)(uVar1 < 0x80000000)) >> 1;
	top = iVar2;
	bottom = iVar2 + iVar3;
	return;
}

// KDXClient.exe: 0044b8c0
void SRect::CenterHoriz(const SRect *inBase)
{
	uint uVar1;
	int iVar2;
	int iVar3;

	iVar3 = right - left;
	uVar1 = (inBase->left + inBase->right) - iVar3;
	iVar2 = (int)((uVar1 + 1) - (uint)(uVar1 < 0x80000000)) >> 1;
	left = iVar2;
	right = iVar2 + iVar3;
	return;
}

// AppearanceEdit.exe: 00439d90
// KDXClient.exe: 004a33e0
void SRect::Constrain(const SRect *inRect)
{
	int iVar1;
	int iVar2;

	iVar1 = inRect->left;
	iVar2 = inRect->right;
	if (left < iVar1)
	{
		left = iVar1;
	}
	else if (iVar2 < left)
	{
		left = iVar2;
	}
	if (right < iVar1)
	{
		right = iVar1;
	}
	else if (iVar2 < right)
	{
		right = iVar2;
	}
	iVar1 = inRect->top;
	iVar2 = inRect->bottom;
	if (top < iVar1)
	{
		top = iVar1;
	}
	else if (iVar2 < top)
	{
		top = iVar2;
	}
	if (bottom < iVar1)
	{
		bottom = iVar1;
	}
	else if (iVar2 < bottom)
	{
		bottom = iVar2;
	}
	return;
}

// AppearanceEdit.app: 1000f070
// AppearanceEdit.exe: 00439c30
// KDXClient.exe: 004a3280
bool SRect::GetIntersection(SRect *inRectA, SRect *inRectB)
{
	int iVar1;
	int iVar2;
	int iVar3;
	int iVar4;

	iVar3 = inRectA->left;
	if (inRectA->left <= inRectB->left)
	{
		iVar3 = inRectB->left;
	}
	iVar1 = inRectA->top;
	if (inRectA->top <= inRectB->top)
	{
		iVar1 = inRectB->top;
	}
	iVar2 = inRectA->right;
	if (inRectB->right <= inRectA->right)
	{
		iVar2 = inRectB->right;
	}
	iVar4 = inRectA->bottom;
	if (inRectB->bottom <= inRectA->bottom)
	{
		iVar4 = inRectB->bottom;
	}
	if ((iVar3 < iVar2) && (iVar1 < iVar4))
	{
		left = iVar3;
		top = iVar1;
		right = iVar2;
		bottom = iVar4;
		return true;
	}
	bottom = 0;
	right = bottom;
	top = right;
	left = top;
	return false;
}

// AppearanceEdit.exe: 00439cb0
// KDXClient.exe: 004a3300
bool SRect::GetUnion(const SRect *inRectA, const SRect *inRectB)
{
	int iVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	int iVar8;

	iVar8 = inRectA->left;
	iVar6 = inRectA->right;
	iVar7 = inRectA->top;
	iVar5 = inRectA->bottom;
	iVar1 = inRectB->left;
	iVar2 = inRectB->top;
	iVar3 = inRectB->right;
	iVar4 = inRectB->bottom;
	if ((iVar8 < iVar6) && (iVar7 < iVar5))
	{
		if ((iVar1 < iVar3) && (iVar2 < iVar4))
		{
			if (iVar1 <= iVar8)
			{
				iVar8 = iVar1;
			}
			left = iVar8;
			if (iVar2 <= iVar7)
			{
				iVar7 = iVar2;
			}
			top = iVar7;
			if (iVar6 <= iVar3)
			{
				iVar6 = iVar3;
			}
			right = iVar6;
			if (iVar5 <= iVar4)
			{
				iVar5 = iVar4;
			}
		}
		else
		{
			left = iVar8;
			top = iVar7;
			right = iVar6;
		}
		bottom = iVar5;
	}
	else
	{
		if ((iVar3 <= iVar1) || (iVar4 <= iVar2))
		{
			bottom = 0;
			right = bottom;
			top = right;
			left = top;
			return false;
		}
		left = iVar1;
		top = iVar2;
		right = iVar3;
		bottom = iVar4;
	}
	return true;
}

// KDXClient.exe: 004a3230
bool SRect::Intersects(const SRect *inRect) const
{
	bool bVar1;
	int iVar2;
	int iVar3;

	bVar1 = false;
	iVar3 = right;
	if (inRect->right <= right)
	{
		iVar3 = inRect->right;
	}
	iVar2 = left;
	if (left <= inRect->left)
	{
		iVar2 = inRect->left;
	}
	if (iVar2 < iVar3)
	{
		iVar3 = bottom;
		if (inRect->bottom <= bottom)
		{
			iVar3 = inRect->bottom;
		}
		iVar2 = top;
		if (top <= inRect->top)
		{
			iVar2 = inRect->top;
		}
		if (iVar2 < iVar3)
		{
			bVar1 = true;
		}
	}
	return bVar1;
}

// KDXClient.exe: 004a3670
void __cdecl SRect::MoveTo(const SRect *inRect, int inLeft, int inTop)
{
	int iVar1;
	int iVar2;

	iVar1 = inRect->right;
	iVar2 = inRect->left;
	left = inLeft;
	right = (iVar1 - iVar2) + inLeft;
	iVar1 = inRect->bottom;
	iVar2 = inRect->top;
	top = inTop;
	bottom = (iVar1 - iVar2) + inTop;
	return;
}

// KDXClient.exe: 004a3450
void SRect::Validate()
{
	int iVar1;

	iVar1 = left;
	if (right < iVar1)
	{
		left = right;
		right = iVar1;
	}
	iVar1 = top;
	if (bottom < iVar1)
	{
		top = bottom;
		bottom = iVar1;
	}
	return;
}
