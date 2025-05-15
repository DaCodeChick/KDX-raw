#pragma once

#include "typedefs.h"

class EXPORT UMath
{
public:
	static double ArcTangent(double x);
	static double Cosine(double x);
	static ulonglong Div64U(ulonglong inNumerator, ulonglong inDenominator);
	static double NormalizeAngle(double x);
	static double Pi();
	static double Sine(double x);
	static double SquareRoot(double x);
};