#pragma once

#include "typedefs.h"

struct EXPORT SRect
{
	int left, right, top, bottom;

	void Constrain(const LPRECT inRect);
	bool GetIntersection(const LPRECT inRectA, const LPRECT inRectB);
	bool GetUnion(const LPRECT inRectA, const LPRECT inRectB);
};

// AppearanceEdit.exe: 00475328
static double gm_2Pi = 6.283185307179586;

// AppearanceEdit.exe: 00475340
static double gm_Pi = 3.141592653589793;
