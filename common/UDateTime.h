#pragma once

#include "typedefs.h"

/// @brief Represents a date and time structure.
struct SCalendarDate
{
	short field1_0x0;
	short year;
	short month;
	short day;
	short hour;
	short minute;
	short second;
	short weekDay;
};

/// @brief Utility class for date and time operations.
class EXPORT UDateTime
{
public:
	static ulonglong GetElapsedTime();
	static int GetMilliseconds();
	static int GetTimeZoneOffset();
};
