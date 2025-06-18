#include "UError.h"

// AppearanceEdit.exe: 00424ae0
// KDXClient.exe: 004716c0
// KDXClient.lexe: 080a9b44
// KDXServer.app: 10030510
// KDXServer.command: 00033628
void __Fail(uint inID)
{
	SError err;
	err.id = inID;
	err.field1_0x4 = 0;
	err.field2_0x8 = 0;
	err.field3_0xc = 0;
	err.field4_0x10 = 0;
	throw err;
}

// AppearanceEdit.exe: 00416560
uint _OSToGenError(int inError)
{
	uint uVar1;

	if ((9999 < inError) && (inError < 12000))
	{
		if (inError == WSAEADDRINUSE)
		{
			uVar1 = 0x40069;
		}
		else if (inError == WSAEADDRINUSE + 1)
		{
			uVar1 = 0x40069;
		}
		else if (inError == WSAENETDOWN)
		{
			uVar1 = 0x4006f;
		}
		else if (inError == WSAENETUNREACH)
		{
			uVar1 = 0x4006f;
		}
		else if (inError == WSAENETRESET)
		{
			uVar1 = 0x4006d;
		}
		else if (inError == WSAECONNABORTED)
		{
			uVar1 = 0x4006d;
		}
		else if (inError == WSAECONNRESET)
		{
			uVar1 = 0x4006a;
		}
		else if (inError == WSAENOBUFS)
		{
			uVar1 = 0x40068;
		}
		else if (inError == WSAETOOMANYREFS)
		{
			uVar1 = 0x40068;
		}
		else if (inError == WSAETIMEDOUT)
		{
			uVar1 = 0x4006c;
		}
		else if (inError == WSAECONNREFUSED)
		{
			uVar1 = 0x4006b;
		}
		else if (inError == WSAEHOSTDOWN)
		{
			uVar1 = 0x4006d;
		}
		else if (inError == WSAEHOSTUNREACH)
		{
			uVar1 = 0x4006f;
		}
		else if (inError == WSAHOST_NOT_FOUND)
		{
			uVar1 = 0x40067;
		}
		else if (inError == WSATRY_AGAIN)
		{
			uVar1 = 0x40067;
		}
		else if (inError == WSANO_DATA)
		{
			uVar1 = 0x40067;
		}
		else
		{
			uVar1 = 0x40064;
		}
		return uVar1;
	}
	if (inError == ERROR_FILE_NOT_FOUND)
	{
		uVar1 = 0x30067;
	}
	else if (inError == ERROR_FILE_NOT_FOUND + 1)
	{
		uVar1 = 0x30066;
	}
	else if (inError == ERROR_ACCESS_DENIED)
	{
		uVar1 = 0x10014;
	}
	else if (inError == ERROR_INVALID_HANDLE)
	{
		uVar1 = 0x20066;
	}
	else if (inError == ERROR_NOT_ENOUGH_MEMORY)
	{
		uVar1 = 0x20065;
	}
	else if (inError == ERROR_INVALID_BLOCK)
	{
		uVar1 = 0x20066;
	}
	else if (inError == ERROR_SHARING_VIOLATION)
	{
		uVar1 = 0x30075;
	}
	else if (inError == ERROR_FILE_EXISTS)
	{
		uVar1 = 0x30073;
	}
	else if (inError == ERROR_INVALID_PARAMETER)
	{
		uVar1 = 0x10002;
	}
	else if (inError == ERROR_DISK_FULL)
	{
		uVar1 = 0x30070;
	}
	else if (inError == ERROR_INVALID_NAME)
	{
		uVar1 = 0x30076;
	}
	else if (inError == ERROR_BAD_PATHNAME)
	{
		uVar1 = 0x30076;
	}
	else if (inError == ERROR_ALREADY_EXISTS)
	{
		uVar1 = 0x30073;
	}
	else if (inError == ERROR_FILENAME_EXCED_RANGE)
	{
		uVar1 = 0x30076;
	}
	else if (inError == ERROR_UNRECOGNIZED_VOLUME)
	{
		uVar1 = 0x30066;
	}
	else if (inError == ERROR_PRIVILEGE_NOT_HELD)
	{
		uVar1 = 0x10014;
	}
	else
	{
		uVar1 = 0x1001b;
	}
	return uVar1;
}
