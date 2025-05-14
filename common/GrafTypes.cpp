#include "GrafTypes.h"

void SRect::Constrain(const LPRECT inRect)
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

bool SRect::GetIntersection(LPRECT inRectA, LPRECT inRectB)
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

bool __cdecl SRect::GetUnion(const LPRECT inRectA, const LPRECT inRectB)
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
