#pragma once

#include "typedefs.h"

struct EXPORT SRect
{
	int left, right, top, bottom;

	void Align(const LPRECT inSourceRect, uint inOptions, const LPRECT inRefRect);
	void Center(const LPRECT inBase, const LPRECT inContainer);
	void CenterHoriz(const LPRECT inBase);
	void Constrain(const LPRECT inRect);
	bool GetIntersection(const LPRECT inRectA, const LPRECT inRectB);
	bool GetUnion(const LPRECT inRectA, const LPRECT inRectB);
	bool Intersects(const LPRECT inRect) const;
	void MoveTo(const LPRECT inRect, int inLeft, int inTop);
	void Validate();
};

// AppearanceEdit.exe: 00475328
static double gm_2Pi = 6.283185307179586;

// AppearanceEdit.app: 10076cf8
// AppearanceEdit.exe: 00475340
static double gm_Pi = 3.141592653589793;
