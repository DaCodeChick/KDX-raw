#pragma once

#include "typedefs.h"

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

class EXPORT UDateTime
{
public:
	static int GetMilliseconds();
	static int GetTimeZoneOffset();
};
