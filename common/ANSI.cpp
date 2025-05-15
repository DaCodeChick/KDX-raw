#include "ANSI.h"

// AppearanceEdit.exe: 00430b70
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

// AppearanceEdit.exe: 00430a00
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
