#pragma once

#include "GrafTypes.h"

class EXPORT UMouse
{
public:
	static uint GetDoubleClickTime();
	static uint GetImage();
	static void GetLocation(SPoint *outLoc);
	static void SetImage(uint inID);
};
