#include "UDateTime.h"

int UDateTime::GetMilliseconds(void)
{
	DWORD DVar1;

	DVar1 = GetTickCount();
	return DVar1;
}

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
