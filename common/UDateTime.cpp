#include "UDateTime.h"

// AppearanceEdit.app: 1004caf0
// AppearanceEdit.exe: 00415710
int UDateTime::GetMilliseconds(void)
{
	DWORD DVar1;

	DVar1 = GetTickCount();
	return DVar1;
}

// AppearanceEdit.app: 1004cb70
// AppearanceEdit.exe: 004157a0
// KDXClient.exe: 00457f40
// KDXServer.app: 1005f9a0
// KDXServer.command: 00018bbc
int UDateTime::GetTimeZoneOffset(void)
{
	DWORD DVar1;
	_TIME_ZONE_INFORMATION local_b0;

	DVar1 = GetTimeZoneInformation(&local_b0);
	if (DVar1 == 2)
	{
		local_b0.Bias = local_b0.Bias + local_b0.DaylightBias;
	}
	return local_b0.Bias * -0x3c;
}
