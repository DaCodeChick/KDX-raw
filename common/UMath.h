#pragma once

#include "typedefs.h"

class EXPORT UMath
{
public:
	static double ArcTangent(double x);
	static uint CalcRandomSeed();
	static double Cosine(double x);
	static ulonglong Div64U(ulonglong inNumerator, ulonglong inDenominator);
	static int GetRandom(uint *ioInit, int inMin, int inMax);
	static uint GetRandom();
	static void GetRandom(void *ioData, uint inDataSize);
	static double NormalizeAngle(double x);
	static double Pi();
	static double Sine(double x);
	static double SquareRoot(double x);
};