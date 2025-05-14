#pragma once

#include "typedefs.h"

struct SRect
{
	int left, right, top, bottom;

	void Constrain(const LPRECT inRect);
	bool GetIntersection(const LPRECT inRectA, const LPRECT inRectB);
	bool GetUnion(const LPRECT inRectA, const LPRECT inRectB);
};
