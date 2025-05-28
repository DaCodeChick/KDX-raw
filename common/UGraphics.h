#pragma once

#include "typedefs.h"

class EXPORT UGraphics
{
public:
	/**
	 * @brief Adjusts the color of a given color by a specified factor, applying a bleed effect.
	 * 
	 * @param inColor 
	 * @param inFactor 
	 * @return uint 
	 */
	static uint AdjustColorWithBleed(uint inColor, int inFactor);
	
	/**
	 * @brief Blends the color channels of a given color by a specified factor, applying a bleed effect.
	 * 
	 * @param inColor
	 * @param inFactor 
	 * @return uint 
	 */
	static uint BlendColorChannels(uint inColor, int inFactor);
	
	/**
	 * @brief Reduces the color channels of a given color by a specified factor, applying a bleed effect.
	 * 
	 * @param inColor
	 * @param inFactor 
	 * @return uint 
	 */
	static uint ReduceColorWithBleed(uint inColor, int inFactor);
	
	/**
	 * @brief Scales the color channels of a given color by a specified factor.
	 * 
	 * @param inColor
	 * @param inFactor 
	 * @return uint
	 */
	static uint ScaleColorChannels(uint inColor, int inFactor);
};
