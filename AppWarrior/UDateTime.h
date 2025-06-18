#pragma once

#include "typedefs.h"

/// @brief Represents a date and time structure.
struct SCalendarDate
{
	short field1_0x0;
	short year;    ///< Year of the date.
	short month;   ///< Month of the date.
	short day;     ///< Day of the date.
	short hour;    ///< Hour of the date.
	short minute;  ///< Minute of the date.
	short second;  ///< Second of the date.
	short weekDay; ///< Weekday of the date.
};

/// @brief Utility class for date and time operations.
class EXPORT UDateTime
{
public:
	/**
	 * @brief Get the elapsed time in microseconds.
	 *
	 * @return Elapsed time in microseconds.
	 */
	static ulonglong GetElapsedTime();

	/**
	 * @brief Get the elapsed time in milliseconds.
	 *
	 * @return Elapsed time in milliseconds.
	 */
	static int GetMilliseconds();

	/**
	 * @brief Get the time zone offset.
	 *
	 * @return Time zone offset in minutes.
	 */
	static int GetTimeZoneOffset();
};
