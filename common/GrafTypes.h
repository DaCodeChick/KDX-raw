#pragma once

#include "typedefs.h"

/// @brief A point structure that defines a point in 2D space.
struct EXPORT SPoint
{
	int x; ///< The x-coordinate of the point.
	int y; ///< The y-coordinate of the point.
};

/// @brief A rectangle structure that defines a rectangular area in 2D space.
struct EXPORT SRect
{
	int left;   ///< The x-coordinate of the left edge of the rectangle.
	int right;  ///< The x-coordinate of the right edge of the rectangle.
	int top;    ///< The y-coordinate of the top edge of the rectangle.
	int bottom; ///< The y-coordinate of the bottom edge of the rectangle.

	/**
	 * @brief Aligns the rectangle with the specified reference rectangle.
	 *
	 * @param inSourceRect The source rectangle to align.
	 * @param inOptions Alignment options.
	 * @param inRefRect The reference rectangle to align with.
	 */
	void Align(const SRect *inSourceRect, uint inOptions, const SRect *inRefRect);

	/**
	 * @brief Centers the rectangle within the specified base rectangle.
	 *
	 * @param inBase The base rectangle to center within.
	 * @param inContainer The container rectangle to constrain the centered rectangle.
	 */
	void Center(const SRect *inBase, const SRect *inContainer);

	/**
	 * @brief Centers the rectangle horizontally within the specified base rectangle.
	 *
	 * @param inBase The base rectangle to center within.
	 */
	void CenterHoriz(const SRect *inBase);

	/**
	 * @brief Constrains the rectangle to fit within the specified rectangle.
	 *
	 * @param inRect The rectangle to constrain the current rectangle within.
	 */
	void Constrain(const SRect *inRect);

	/**
	 * @brief Gets the intersection of two rectangles.
	 *
	 * @param inRectA The first rectangle.
	 * @param inRectB The second rectangle.
	 * @return true if the intersection was found, false otherwise.
	 */
	bool GetIntersection(const SRect *inRectA, const SRect *inRectB);

	/**
	 * @brief Calculates the union of two rectangles and stores the result in the current rectangle.
	 *
	 * @param inRectA The first rectangle.
	 * @param inRectB The second rectangle.
	 * @return true if the union was successfully calculated, false if the rectangles do not
	 * intersect.
	 */
	bool GetUnion(const SRect *inRectA, const SRect *inRectB);

	/**
	 * @brief Checks if the rectangle intersects with another rectangle.
	 *
	 * @param inRect The rectangle to check for intersection.
	 * @return true if the rectangles intersect, false otherwise.
	 */
	bool Intersects(const SRect *inRect) const;

	/**
	 * @brief Moves the rectangle to a new position defined by the specified left and top
	 * coordinates.
	 *
	 * @param inRect
	 * @param inLeft The new left coordinate of the rectangle.
	 * @param inTop The new top coordinate of the rectangle.
	 */
	void MoveTo(const SRect *inRect, int inLeft, int inTop);

	/// @brief Validates the rectangle's dimensions.
	void Validate();
};

// AppearanceEdit.exe: 00475328
/// @brief A constant representing the value of 2π (2 times Pi).
static double gm_2Pi = 6.283185307179586;

// AppearanceEdit.app: 10076cf8
// AppearanceEdit.exe: 00475340
/// @brief A constant representing the value of Pi.
static double gm_Pi = 3.141592653589793;
