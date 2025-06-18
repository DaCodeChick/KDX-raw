#pragma once

#include "UMemory.h"

/// @brief A utility class for text operations.
class EXPORT UText
{
public:
	/**
	 * @brief Decodes a UTF-8 character from the input text.
	 *
	 * @param inText The input text buffer.
	 * @param inSize The size of the input text buffer.
	 * @param outSize The size of the decoded character.
	 * @return The decoded UTF-8 character.
	 */
	static uint DecodeUTF8Char(const void *inText, size_t inSize, size_t *outSize);

	/**
	 * @brief Compares two strings for equality.
	 *
	 * @param inTextA The first string to compare.
	 * @param inTextB The second string to compare.
	 * @param inSize The size of the strings to compare.
	 * @return True if the strings are equal, false otherwise.
	 */
	static bool Equal(const char *inTextA, const char *inTextB, size_t inSize);

	/**
	 * @brief Checks if a character is an alphanumeric character.
	 *
	 * @param inChar The character to check.
	 * @return true if the character is alphanumeric, false otherwise.
	 */
	static bool IsAlphaNumeric(uint inChar);

	/**
	 * @brief Checks if a character is a hexadecimal digit.
	 *
	 * @param inChar The character to check.
	 * @return true if the character is a hexadecimal digit, false otherwise.
	 */
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

	/**
	 * @brief Converts a UTF-8 encoded string to a UTF-16 encoded string.
	 *
	 * @param inText The input UTF-8 text buffer.
	 * @param inSize The size of the input text buffer.
	 * @return The handle to the allocated UTF-16 text buffer.
	 */
	static THdl UTF8ToUTF16(const void *inText, size_t inSize);
};
