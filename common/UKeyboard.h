#pragma once

#include "typedefs.h"

/// @brief Keyboard utility class.
class EXPORT UKeyboard
{
public:
	/**
	 * @brief Converts a key code and modifier keys to a character.
	 *
	 * @param inKeyCode The key code to convert.
	 * @param inMods The modifier keys (e.g., Shift, Ctrl).
	 * @return The character representation of the key code with modifiers applied.
	 */
	static uint KeyToChar(ushort inKeyCode, uint inMods);
};
