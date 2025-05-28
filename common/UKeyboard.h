#pragma once

#include "typedefs.h"

/// @brief Keyboard utility class.
class EXPORT UKeyboard
{
public:
	/**
	 * @brief Converts a key code and modifier keys to a character.
	 * 
	 * @param inKeyCode
	 * @param inMods 
	 * @return uint 
	 */
	static uint KeyToChar(ushort inKeyCode, uint inMods);
};
