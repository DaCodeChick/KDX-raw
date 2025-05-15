#pragma once

#include "typedefs.h"

class EXPORT UGraphics
{
public:
	static uint AdjustColorWithBleed(uint inColor, int inFactor);
	static uint BlendColorChannels(uint inColor, int inFactor);
	static uint ReduceColorWithBleed(uint inColor, int inFactor);
	static uint ScaleColorChannels(uint inColor, int inFactor);
};
