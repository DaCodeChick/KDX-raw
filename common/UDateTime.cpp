#include "UDateTime.h"
#include "UMath.h"

#ifdef _WIN32
// KDXClient.exe: 004fedd0
static FILETIME gElapsed = {0};

// KDXClient.exe: 004fedd8
static FILETIME gLastRecorded = {0};
#else
#endif // _WIN32

// KDXClient.exe: 00457dc0
ulonglong UDateTime::GetElapsedTime(void)
{
	ulonglong uVar1;
	_FILETIME local_18;

	GetSystemTimeAsFileTime(&local_18);
	if ((local_18.dwHighDateTime <= gLastRecorded.dwHighDateTime) &&
	    ((local_18.dwHighDateTime != gLastRecorded.dwHighDateTime ||
	      (local_18.dwLowDateTime <= gLastRecorded.dwLowDateTime))))
	{
		gLastRecorded.dwLowDateTime = local_18.dwLowDateTime;
		gLastRecorded.dwHighDateTime = local_18.dwHighDateTime;
		return CONCAT44(gElapsed.dwHighDateTime, gElapsed.dwLowDateTime);
	}
	uVar1 = UMath::Div64U(CONCAT44((local_18.dwHighDateTime - gLastRecorded.dwHighDateTime) -
	                                   (uint)(local_18.dwLowDateTime < gLastRecorded.dwLowDateTime),
	                               local_18.dwLowDateTime - gLastRecorded.dwLowDateTime),
	                      10);
	gLastRecorded.dwLowDateTime = local_18.dwLowDateTime;
	gLastRecorded.dwHighDateTime = local_18.dwHighDateTime;
	uVar1 = uVar1 + CONCAT44(gElapsed.dwHighDateTime, gElapsed.dwLowDateTime);
	gElapsed.dwLowDateTime = (DWORD)uVar1;
	gElapsed.dwHighDateTime = (DWORD)(uVar1 >> 0x20);
	return uVar1;
}

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
	if (DVar1 == TIME_ZONE_ID_DAYLIGHT)
	{
		local_b0.Bias = local_b0.Bias + local_b0.DaylightBias;
	}
	return local_b0.Bias * -0x3c;
}
