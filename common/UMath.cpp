#include "UMath.h"
#include "GrafTypes.h"
#include "UMemory.h"

#include <cmath>

// KDXServer.exe: 00481198
static uint gRandomSeed = 0;

// KDXServer.exe: 00481098
static uint gState[64] = {0};

// KDXServer.exe: 0048119c
static byte gIndex = 0;

// AppearanceEdit.exe: 0044db10
double UMath::ArcTangent(double x)
{
	// tweak: decompilation goofed here, just wrap to std::atan
	return std::atan(x);
}

// KDXServer.exe: 0042f760
uint UMath::CalcRandomSeed(void)
{
	_FILETIME local_c;

	GetSystemTimeAsFileTime(&local_c);
	return local_c.dwLowDateTime;
}

// AppearanceEdit.exe: 0044daf0
double UMath::Cosine(double x)
{
	// tweak: decompilation goofed here, just wrap to std::cos
	return std::cos(NormalizeAngle(x));
}

// AppearanceEdit.app: 1005e3a0
// AppearanceEdit.exe: 00445950
ulonglong UMath::Div64U(ulonglong inNumerator, ulonglong inDenominator)
{
	// tweak: don't bother with the antiquated 32-bit shifting nonsense
	return inNumerator / inDenominator;
}

// KDXServer.exe: 00435380
uint UMath::GetRandom(void)
{
	DWORD inInit;
	uint uVar1;

	inInit = CalcRandomSeed();
	uVar1 = UMemory::Checksum(gState, 0x100, inInit);
	if (gRandomSeed == 0)
	{
		gRandomSeed = inInit;
	}
	gRandomSeed = gRandomSeed * 0x41c64e6d + 0x3039;
	uVar1 = uVar1 ^ gRandomSeed;
	gState[gIndex] = gState[gIndex] ^ uVar1;
	gIndex = (byte)uVar1 & 0x3f;
	return uVar1;
}

// AppearanceEdit.exe: 0044dab0
double UMath::NormalizeAngle(double x)
{
	// tweak: decompilation goofed here, just fmod with 2PI
	x = std::fmod(x, gm_2Pi);
	if (x < 0)
		x += gm_2Pi;

	return x;
}

// AppearanceEdit.app: 1001d620
// AppearanceEdit.exe: 0044db30
double UMath::Pi()
{
	return gm_Pi;
}

// AppearanceEdit.exe: 0044dad0
double UMath::Sine(double x)
{
	// tweak: decompilation goofed here, just wrap to std::sin
	return std::sin(NormalizeAngle(x));
}

// AppearanceEdit.exe: 0044db20
double UMath::SquareRoot(double x)
{
	// tweak: wrap to std::sqrt instead of using x86's FSQRT assembly instruction
	return std::sqrt(x);
}
