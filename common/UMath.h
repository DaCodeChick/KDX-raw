#pragma once

#include "typedefs.h"

/// @brief A collection of mathematical functions and utilities.
class EXPORT UMath
{
public:
	/**
	 * @brief Calculates the arc tangent of a value.
	 *
	 * @param x The value for which to calculate the arc tangent.
	 * @return The arc tangent of the value.
	 */
	static double ArcTangent(double x);

	static uint CalcRandomSeed();

	/**
	 * @brief Calculates the cosine of a value.
	 *
	 * @param x The value for which to calculate the cosine.
	 * @return The cosine of the value.
	 */
	static double Cosine(double x);

	/**
	 * @brief Divides two unsigned long long integers and returns the result as an unsigned long
	 * long.
	 *
	 * @param inNumerator The numerator of the division.
	 * @param inDenominator The denominator of the division.
	 * @return The result of the division as an unsigned long long.
	 */
	static ulonglong Div64U(ulonglong inNumerator, ulonglong inDenominator);

	/**
	 * @brief Generates a random integer within a specified range.
	 *
	 * @param ioInit Pointer to an unsigned integer used for random number generation
	 * initialization.
	 * @param inMin The minimum value of the range (inclusive).
	 * @param inMax The maximum value of the range (exclusive).
	 * @return A random integer within the specified range.
	 */
	static int GetRandom(uint *ioInit, int inMin, int inMax);

	/**
	 * @brief Generates a random unsigned integer.
	 *
	 * @return A random unsigned integer.
	 */
	static uint GetRandom();

	/**
	 * @brief Fills a block of memory with random data.
	 *
	 * @param ioData Pointer to the memory block to fill with random data.
	 * @param inDataSize The size of the memory block in bytes.
	 */
	static void GetRandom(void *ioData, uint inDataSize);

	/**
	 * @brief Normalizes an angle to the range of -π to π.
	 *
	 * @param x The angle in radians to normalize.
	 * @return The normalized angle in radians, within the range of -π to π.
	 */
	static double NormalizeAngle(double x);

	static double Pi();

	/**
	 * @brief Calculates the sine of a value.
	 *
	 * @param x The value for which to calculate the sine.
	 * @return The sine of the value.
	 */
	static double Sine(double x);

	/**
	 * @brief Calculates the square root of a value.
	 *
	 * @param x The value for which to calculate the square root.
	 * @return The square root of the value.
	 */
	static double SquareRoot(double x);
};