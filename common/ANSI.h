#pragma once

#include "typedefs.h"

EXPORT uint pstrcat(byte *dst, byte *src);
EXPORT uint pstrcpy(byte *dst, byte *src);
EXPORT uint pstrncat(byte *dst, byte *src, uint len);
EXPORT uint pstrncpy(byte *dst, byte *src, uint len);
#ifndef _WIN32
char *strrev(char *_Str);
#endif // _WIN32
