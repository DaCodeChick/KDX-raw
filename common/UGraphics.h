#pragma once

#include "typedefs.h"

class EXPORT UGraphics
{
public:
	/**
	 * @brief Adjusts the color of a given color by a specified factor, applying a bleed effect.
	 *
	 * @param inColor The color to adjust, represented as an unsigned integer.
	 * @param inFactor The factor by which to adjust the color channels.
	 * @return The adjusted color, represented as an unsigned integer.
	 */
	static uint AdjustColorWithBleed(uint inColor, int inFactor);

	/**
	 * @brief Blends the color channels of a given color by a specified factor, applying a bleed
	 * effect.
	 *
	 * @param inColor The color to blend, represented as an unsigned integer.
	 * @param inFactor The factor by which to blend the color channels.
	 * @return The blended color, represented as an unsigned integer.
	 */
	static uint BlendColorChannels(uint inColor, int inFactor);

	/**
	 * @brief Reduces the color channels of a given color by a specified factor, applying a bleed
	 * effect.
	 *
	 * @param inColor The color to reduce, represented as an unsigned integer.
	 * @param inFactor The factor by which to reduce the color channels.
	 * @return The reduced color, represented as an unsigned integer.
	 */
	static uint ReduceColorWithBleed(uint inColor, int inFactor);

	/**
	 * @brief Scales the color channels of a given color by a specified factor.
	 *
	 * @param inColor The color to scale, represented as an unsigned integer.
	 * @param inFactor The factor by which to scale the color channels.
	 * @return The scaled color, represented as an unsigned integer.
	 */
	static uint ScaleColorChannels(uint inColor, int inFactor);
};
