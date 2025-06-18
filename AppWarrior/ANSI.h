#pragma once

#include "typedefs.h"

/**
 * @brief Concatenate two strings.
 *
 * @param dst Destination string where the result will be stored.
 * @param src Source string to be concatenated.
 * @return The length of the resulting string in bytes, excluding the null terminator.
 */
EXPORT uint pstrcat(byte *dst, byte *src);

/**
 * @brief Find the first occurrence of a character in a string.
 *
 * @param str Source string to be searched.
 * @param chr Character to be found.
 * @return Pointer to the first occurrence of the character in the string, or NULL if not found.
 */
EXPORT byte *pstrchr(const byte *str, byte chr);

/**
 * @brief Compare two strings.
 *
 * @param str1 First string to be compared.
 * @param str2 Second string to be compared.
 * @return True if the strings are equal, false otherwise.
 */
EXPORT bool pstrcmp(const byte *str1, const byte *str2);

/**
 * @brief Copies a string from src to dst.
 *
 * @param dst Destination string where the result will be stored.
 * @param src Source string to be copied.
 * @return The length of the copied string in bytes, excluding the null terminator.
 */
EXPORT uint pstrcpy(byte *dst, byte *src);

/**
 * @brief Concatenate a string to another string with a specified length.
 *
 * @param dst Destination string where the result will be stored.
 * @param src Source string to be concatenated.
 * @param len Length of the source string to be concatenated.
 * @return The length of the resulting string in bytes, excluding the null terminator.
 */
EXPORT uint pstrncat(byte *dst, byte *src, uint len);

/**
 * @brief Copy a string from source to destination with a specified length.
 *
 * @param dst Destination string where the result will be stored.
 * @param src Source string to be copied.
 * @param len Length of the source string to be copied.
 * @return The length of the copied string in bytes, excluding the null terminator.
 */
EXPORT uint pstrncpy(byte *dst, byte *src, uint len);

/**
 * @brief Find the last occurrence of a character in a string.
 *
 * @param str Source string to be searched.
 * @param chr Character to be found.
 * @return Pointer to the last occurrence of the character in the string, or NULL if not found.
 */
EXPORT byte *pstrrchr(const byte *str, byte chr);
#ifndef _WIN32
/**
 * @brief Reverse a string in place.
 *
 * @param _Str Source string to be reversed.
 * @return Pointer to the reversed string.
 */
char *strrev(char *_Str);
#endif // _WIN32
