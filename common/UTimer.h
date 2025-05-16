#pragma once

#include "MoreTypes.h"
#include "typedefs.h"

struct STimer;

class EXPORT UTimer
{
public:
	static void Dispose(STimer *inRef);
	static STimer *New(TMessageProc inProc, void *inContext);
	// static void Start(STimer *inRef, uint inMillisecs, int inIsRepeating);
	static void Stop(STimer *inRef);
};
