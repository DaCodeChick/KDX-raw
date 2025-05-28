#pragma once

#include "GrafTypes.h"

/// @brief Mouse class for handling mouse interactions.
class EXPORT UMouse
{
public:
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
	
	static void SetImage(uint inID);
};
