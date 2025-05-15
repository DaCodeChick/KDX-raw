#include "UMath.h"
#include "GrafTypes.h"

#include <cmath>

// AppearanceEdit.exe: 0044db10
double UMath::ArcTangent(double x)
{
	// decompilation goofed here, just wrap to std::atan
	return std::atan(x);
}

// AppearanceEdit.exe: 0044daf0
double UMath::Cosine(double x)
{
	// decompilation goofed here, just wrap to std::cos
	return std::cos(NormalizeAngle(x));
}

// AppearanceEdit.exe: 00445950
ulonglong UMath::Div64U(ulonglong inNumerator, ulonglong inDenominator)
{
	// don't bother with the antiquated 32-bit shifting nonsense
	return inNumerator / inDenominator;
}

// AppearanceEdit.exe: 0044dab0
double UMath::NormalizeAngle(double x)
{
	// decompilation goofed here, just fmod with 2PI
	x = std::fmod(x, gm_2Pi);
	if (x < 0)
		x += gm_2Pi;

	return x;
}

// AppearanceEdit.exe: 0044db30
double UMath::Pi()
{
	return gm_Pi;
}

// AppearanceEdit.exe: 0044dad0
double UMath::Sine(double x)
{
	// decompilation goofed here, just wrap to std::sin
	return std::sin(NormalizeAngle(x));
}

// AppearanceEdit.exe: 0044db20
double UMath::SquareRoot(double x)
{
	// wrap to std::sqrt instead of using x86's FSQRT assembly instruction
	return std::sqrt(x);
}
