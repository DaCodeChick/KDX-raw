#pragma once

#include "typedefs.h"

/**
 * @brief Concatenate two strings.
 *
 * @param dst
 * @param src
 * @return uint
 */
EXPORT uint pstrcat(byte *dst, byte *src);

/**
 * @brief Find the first occurrence of a character in a string.
 *
 * @param str
 * @param chr
 * @return byte*
 */
EXPORT byte *pstrchr(const byte *str, byte chr);

/**
 * @brief Compare two strings.
 *
 * @param str1
 * @param str2
 * @return bool
 */
EXPORT bool pstrcmp(const byte *str1, const byte *str2);

/**
 * @brief Copies a string from src to dst.
 *
 * @param dst
 * @param src
 * @return uint
 */
EXPORT uint pstrcpy(byte *dst, byte *src);

/**
 * @brief Concatenate a string to another string with a specified length.
 *
 * @param dst
 * @param src
 * @param len
 * @return uint
 */
EXPORT uint pstrncat(byte *dst, byte *src, uint len);

/**
 * @brief Copy a string from source to destination with a specified length.
 *
 * @param dst
 * @param src
 * @param len
 * @return uint
 */
EXPORT uint pstrncpy(byte *dst, byte *src, uint len);

/**
 * @brief Find the last occurrence of a character in a string.
 *
 * @param str
 * @param chr
 * @return byte*
 */
EXPORT byte *pstrrchr(const byte *str, byte chr);
#ifndef _WIN32
/**
 * @brief Reverse a string in place.
 *
 * @param _Str
 * @return char*
 */
char *strrev(char *_Str);
#endif // _WIN32
