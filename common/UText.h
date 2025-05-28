#pragma once

#include "typedefs.h"

/// @brief A utility class for text operations.
class EXPORT UText
{
public:
	/**
	 * @brief Compares two strings for equality.
	 *
	 * @param inTextA
	 * @param inTextB
	 * @param inSize The size of the strings to compare.
	 * @return True if the strings are equal, false otherwise.
	 */
	static bool Equal(const char *inTextA, const char *inTextB, uint inSize);

	static bool IsHex(uint inChar);

	/**
	 * @brief Converts a character to lowercase.
	 *
	 * @param inChar The character to convert.
	 * @return The lowercase version of the character if it is an uppercase letter; otherwise,
	 * returns the character unchanged.
	 */
	static uint ToLower(uint inChar);

	/**
	 * @brief Converts a character to uppercase.
	 *
	 * @param inChar The character to convert.
	 * @return The uppercase version of the character if it is a lowercase letter; otherwise,
	 * returns the character unchanged.
	 */
	static uint ToUpper(uint inChar);
};
