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

#define CARRY4(x, y, carry_in) ((((x) + (y) + (carry_in)) >> 4) & 1)
#define CONCAT11(a, b) ((ushort)(a) << 8 | (ushort)(b))
#define CONCAT13(msb1, lsb3) (((uint)(msb1) << 24) | ((uint)(lsb3) & 0xFFFFFF))
#define CONCAT22(a, b) ((ulong)(a) << 16 | (ulong)(b))
#define CONCAT31(msb3, lsb1) (((uint)(msb3) << 8) | ((uint)(lsb1) & 0xFF))
#define CONCAT44(a, b) ((ulonglong)(a) << 32 | (ulonglong)(b))
#define SUB41(a, b) ((uint)((uint)(a) - (uint)(b)))
