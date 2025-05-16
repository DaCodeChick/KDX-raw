#pragma once

#include "typedefs.h"

struct EXPORT SRect
{
	int left, right, top, bottom;

	void Align(const SRect *inSourceRect, uint inOptions, const SRect *inRefRect);
	void Center(const SRect *inBase, const SRect *inContainer);
	void CenterHoriz(const SRect *inBase);
	void Constrain(const SRect *inRect);
	bool GetIntersection(const SRect *inRectA, const SRect *inRectB);
	bool GetUnion(const SRect *inRectA, const SRect *inRectB);
	bool Intersects(const SRect *inRect) const;
	void MoveTo(const SRect *inRect, int inLeft, int inTop);
	void Validate();

// tweak: Some inline QoL operator overloads for cross platform boilerplate
#ifdef _WIN32
	operator const LPRECT()
	{
		return (LPRECT)this;
	}
	operator LPRECT()
	{
		return (LPRECT)this;
	}
#endif // _WIN32
};

// AppearanceEdit.exe: 00475328
static double gm_2Pi = 6.283185307179586;

// AppearanceEdit.app: 10076cf8
// AppearanceEdit.exe: 00475340
static double gm_Pi = 3.141592653589793;
