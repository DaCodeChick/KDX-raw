#pragma once

#ifdef _WIN32
#include <windows.h>
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#include <cstring>

typedef unsigned char byte;
typedef long long longlong;
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long long ulonglong;
typedef unsigned char undefined;
typedef unsigned char undefined1;
typedef unsigned short undefined2;
typedef unsigned long undefined4;
typedef unsigned long long undefined8;
typedef unsigned short ushort;

#define CONCAT11(a, b) ((ushort)(a) << 8 | (ushort)(b))
#define CONCAT22(a, b) ((ulong)(a) << 16 | (ulong)(b))
#define CONCAT44(a, b) ((ulonglong)(a) << 32 | (ulonglong)(b))
