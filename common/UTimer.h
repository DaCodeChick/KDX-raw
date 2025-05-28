#pragma once

#include "MoreTypes.h"
#include "typedefs.h"

struct STimer;

/// @brief Timer class for managing timed events.
class EXPORT UTimer
{
public:
	/**
	 * @brief Dispose a timer reference.
	 *
	 * @param inRef Pointer to the timer reference to be disposed.
	 */
	static void Dispose(STimer *inRef);

	/**
	 * @brief Create a new timer reference.
	 *
	 * @param inProc Callback function to be called when the timer expires.
	 * @param inContext Context pointer to be passed to the callback function.
	 * @return Pointer to the newly created timer reference.
	 */
	static STimer *New(TMessageProc inProc, void *inContext);
	// static void Start(STimer *inRef, uint inMillisecs, int inIsRepeating);

	static void Stop(STimer *inRef);
};
