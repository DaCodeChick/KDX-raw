#pragma once

#include "GrafTypes.h"

/// @brief Mouse class for handling mouse interactions.
class EXPORT UMouse
{
public:
	/**
	 * @brief Gets the time interval for double-click detection.
	 *
	 * @return The double-click time in milliseconds.
	 */
	static uint GetDoubleClickTime();

	/**
	 * @brief Retrieves the current mouse image ID.
	 *
	 * @return The ID of the current mouse image.
	 */
	static uint GetImage();

	/**
	 * @brief Retrieves the current mouse location.
	 *
	 * @param outLoc Pointer to an SPoint structure where the mouse location will be stored.
	 */
	static void GetLocation(SPoint *outLoc);

	/**
	 * @brief Sets the current mouse image ID.
	 *
	 * @param inID The ID of the new mouse image.
	 */
	static void SetImage(uint inID);
};
