#pragma once

#include "typedefs.h"

class EXPORT UMouse
{
public:
	static uint GetDoubleClickTime();
	static uint GetImage();
	static void GetLocation(LPPOINT outLoc);
	static void SetImage(uint inID);
};
