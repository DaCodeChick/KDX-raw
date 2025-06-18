#include "ANSI.h"

// AppearanceEdit.app: 100093f0
// AppearanceEdit.exe: 00430b70
// KDXClient.exe: 00467d70
// KDXServer.exe: 00428a30
uint pstrcat(byte *dst, byte *src)
{
	uint uVar1;
	uint uVar2;
	uint local_10;
	uint local_c;

	if (dst == NULL)
	{
		return 0;
	}
	uVar1 = (uint)*dst;
	if (src == NULL)
	{
		return uVar1;
	}
	local_10 = (uint)*src;
	local_c = uVar1 + local_10;
	if (0xff < local_c)
	{
		local_c = 0xff;
		local_10 = 0xff - uVar1;
	}
	*dst = (byte)local_c;
	uVar2 = 1;
	if (local_10 != 0)
	{
		if (8 < local_10)
		{
			do
			{
				dst[uVar2 + uVar1] = src[uVar2];
				dst[uVar2 + uVar1 + 1] = src[uVar2 + 1];
				dst[uVar2 + uVar1 + 2] = src[uVar2 + 2];
				dst[uVar2 + uVar1 + 3] = src[uVar2 + 3];
				dst[uVar2 + uVar1 + 4] = src[uVar2 + 4];
				dst[uVar2 + uVar1 + 5] = src[uVar2 + 5];
				dst[uVar2 + uVar1 + 6] = src[uVar2 + 6];
				dst[uVar2 + uVar1 + 7] = src[uVar2 + 7];
				uVar2 = uVar2 + 8;
			} while (uVar2 <= local_10 - 8);
		}
		for (; uVar2 <= local_10; uVar2 = uVar2 + 1)
		{
			dst[uVar2 + uVar1] = src[uVar2];
		}
	}
	return local_c;
}

// KDXServer.exe: 00428e20
byte *pstrchr(byte *str, byte chr)
{
	uint uVar1;

	if (str == NULL)
	{
		return str;
	}
	uVar1 = 0;
	if (*str != 0)
	{
		do
		{
			if (chr == str[uVar1 + 1])
			{
				return str + uVar1 + 1;
			}
			uVar1 = uVar1 + 1;
		} while (uVar1 < *str);
	}
	return NULL;
}

// AppearanceEdit.app 10009780
// KDXServer.exe: 00428d80
bool __cdecl pstrcmp(byte *str1, byte *str2)
{
	uint uVar1;
	uint uVar2;

	if (str1 == NULL)
	{
		uVar1 = 0;
	}
	else
	{
		uVar1 = (uint)*str1;
	}
	if (str2 == NULL)
	{
		uVar2 = 0;
	}
	else
	{
		uVar2 = (uint)*str2;
	}
	if (uVar1 == uVar2)
	{
		uVar2 = 1;
		if (uVar1 != 0)
		{
			do
			{
				if (str1[uVar2] != str2[uVar2])
				{
					return false;
				}
				uVar2 = uVar2 + 1;
			} while (uVar2 <= uVar1);
		}
		return true;
	}
	return false;
}

// AppearanceEdit.exe: 00430a00
// KDXClient.exe: 00467c00
uint pstrcpy(byte *dst, byte *src)

{
	uint uVar1;
	uint uVar2;

	if (dst == NULL)
	{
		return 0;
	}
	if (src == NULL)
	{
		uVar1 = 0;
	}
	else
	{
		uVar1 = (uint)*src;
	}
	*dst = (byte)uVar1;
	uVar2 = 1;
	if (uVar1 != 0)
	{
		if (8 < uVar1)
		{
			do
			{
				dst[uVar2] = src[uVar2];
				dst[uVar2 + 1] = src[uVar2 + 1];
				dst[uVar2 + 2] = src[uVar2 + 2];
				dst[uVar2 + 3] = src[uVar2 + 3];
				dst[uVar2 + 4] = src[uVar2 + 4];
				dst[uVar2 + 5] = src[uVar2 + 5];
				dst[uVar2 + 6] = src[uVar2 + 6];
				dst[uVar2 + 7] = src[uVar2 + 7];
				uVar2 = uVar2 + 8;
			} while (uVar2 <= uVar1 - 8);
		}
		for (; uVar2 <= uVar1; uVar2 = uVar2 + 1)
		{
			dst[uVar2] = src[uVar2];
		}
	}
	return uVar1;
}

// AppearanceEdit.exe: 00430c60
// KDXClient.exe: 00467e60
uint pstrncat(byte *dst, byte *src, uint len)
{
	uint uVar1;
	uint uVar2;
	uint local_10;
	uint local_c;

	if (dst == NULL)
	{
		return 0;
	}
	uVar1 = (uint)*dst;
	if (src == NULL)
	{
		return uVar1;
	}
	local_10 = (uint)*src;
	if (len < local_10)
	{
		local_10 = len;
	}
	local_c = uVar1 + local_10;
	if (0xff < local_c)
	{
		local_c = 0xff;
		local_10 = 0xff - uVar1;
	}
	*dst = (byte)local_c;
	uVar2 = 1;
	if (local_10 != 0)
	{
		if (8 < local_10)
		{
			do
			{
				dst[uVar2 + uVar1] = src[uVar2];
				dst[uVar2 + uVar1 + 1] = src[uVar2 + 1];
				dst[uVar2 + uVar1 + 2] = src[uVar2 + 2];
				dst[uVar2 + uVar1 + 3] = src[uVar2 + 3];
				dst[uVar2 + uVar1 + 4] = src[uVar2 + 4];
				dst[uVar2 + uVar1 + 5] = src[uVar2 + 5];
				dst[uVar2 + uVar1 + 6] = src[uVar2 + 6];
				dst[uVar2 + uVar1 + 7] = src[uVar2 + 7];
				uVar2 = uVar2 + 8;
			} while (uVar2 <= local_10 - 8);
		}
		for (; uVar2 <= local_10; uVar2 = uVar2 + 1)
		{
			dst[uVar2 + uVar1] = src[uVar2];
		}
	}
	return local_c;
}

// AppearanceEdit.exe: 00430ab0
// KDXClien.exe: 00467cb0
uint pstrncpy(byte *dst, byte *src, uint len)
{
	uint uVar1;
	uint uVar2;

	if (dst == NULL)
	{
		return 0;
	}
	if (src == NULL)
	{
		uVar1 = 0;
	}
	else
	{
		uVar1 = (uint)*src;
	}
	if (len < uVar1)
	{
		uVar1 = len;
	}
	*dst = (byte)uVar1;
	uVar2 = 1;
	if (uVar1 != 0)
	{
		if (8 < uVar1)
		{
			do
			{
				dst[uVar2] = src[uVar2];
				dst[uVar2 + 1] = src[uVar2 + 1];
				dst[uVar2 + 2] = src[uVar2 + 2];
				dst[uVar2 + 3] = src[uVar2 + 3];
				dst[uVar2 + 4] = src[uVar2 + 4];
				dst[uVar2 + 5] = src[uVar2 + 5];
				dst[uVar2 + 6] = src[uVar2 + 6];
				dst[uVar2 + 7] = src[uVar2 + 7];
				uVar2 = uVar2 + 8;
			} while (uVar2 <= uVar1 - 8);
		}
		for (; uVar2 <= uVar1; uVar2 = uVar2 + 1)
		{
			dst[uVar2] = src[uVar2];
		}
	}
	return uVar1;
}

// KDXServer.exe: 00428e60
byte *pstrrchr(byte *str, byte chr)
{
	byte *pbVar1;
	byte *pbVar2;

	if (str == NULL)
	{
		return str;
	}
	pbVar2 = str + *str;
	do
	{
		pbVar1 = pbVar2;
		if (pbVar1 <= str)
		{
			return NULL;
		}
		pbVar2 = pbVar1 + -1;
	} while (*pbVar1 != chr);
	return pbVar1;
}

// AppearanceEdit.exe: 0044d2f0
#ifndef _WIN32
char *strrev(char *_Str)
{
	char cVar1;
	int iVar2;
	int iVar3;
	char *pcVar4;

	if (_Str == NULL)
	{
		return NULL;
	}
	iVar3 = 0;
	iVar2 = -1;
	pcVar4 = _Str;
	do
	{
		if (iVar2 == 0)
			break;
		iVar2 = iVar2 + -1;
		cVar1 = *pcVar4;
		pcVar4 = pcVar4 + 1;
	} while (cVar1 != '\0');
	iVar2 = -3 - iVar2;
	if (0 < iVar2)
	{
		do
		{
			cVar1 = _Str[iVar3];
			_Str[iVar3] = _Str[iVar2];
			_Str[iVar2] = cVar1;
			iVar3 = iVar3 + 1;
			iVar2 = iVar2 + -1;
		} while (iVar3 < iVar2);
	}
	return _Str;
}
#endif // _WIN32
