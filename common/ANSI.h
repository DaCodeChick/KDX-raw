#pragma once

#include "typedefs.h"

EXPORT uint pstrcat(byte *dst, byte *src);
EXPORT byte *pstrchr(const byte *str, byte chr);
EXPORT bool pstrcmp(const byte *str1, const byte *str2);
EXPORT uint pstrcpy(byte *dst, byte *src);
EXPORT uint pstrncat(byte *dst, byte *src, uint len);
EXPORT uint pstrncpy(byte *dst, byte *src, uint len);
EXPORT byte *pstrrchr(const byte *str, byte chr);
#ifndef _WIN32
char *strrev(char *_Str);
#endif // _WIN32
