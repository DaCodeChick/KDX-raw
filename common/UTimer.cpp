#include "UTimer.h"
#include "CPtrList.h"
#include "UError.h"
#include "UMemory.h"

struct STimer
{
	STimer *next;
	uint tag;
	UINT_PTR winTimer;
	TMessageProc msgProc;
	void *msgProcContext;
	bool onceOnly;
};

// KDXClient.lexe: 081a0c40
static uint gTimerCount = 0;

// KDXServer.exe: 00481258
static CPtrList<STimer> gTimers;

// KDXServer.exe: 0042f250
void UTimer::Dispose(STimer *inRef)
{
	if (inRef == NULL)
	{
		return;
	}
	if (inRef->tag != 0x1f0d2b21)
	{
		return;
	}
	if (inRef->winTimer != 0)
	{
		KillTimer(NULL, inRef->winTimer);
		inRef->winTimer = 0;
		gTimers.RemoveItem(inRef);
	}
	return;
}

// KDXServer.exe: 0042f070
STimer *UTimer::New(TMessageProc inProc, void *inContext)
{
	STimer *pvVar1;

	if (inProc == NULL)
	{
		__Fail(0x10002);
	}

	// tweak: ensure correct STimer size
	pvVar1 = (STimer *)UMemory::NewClear(sizeof(STimer));

	pvVar1->msgProc = inProc;
	pvVar1->msgProcContext = inContext;
	pvVar1->tag = 0x1f0d2b21;
	gTimerCount = gTimerCount + 1;
	gTimers.AddItem(pvVar1);
	return pvVar1;
}

// KDXServer.exe: 0042f150
void UTimer::Stop(STimer *inRef)
{
	STimer *inPtr;

	inPtr = inRef->next;
	if (inPtr == NULL)
	{
		return;
	}
	if (inPtr->tag != 0x1f0d2b21)
	{
		inRef->next = NULL;
		return;
	}
	inPtr->tag = 0;
	if (inPtr->winTimer != 0)
	{
		KillTimer(NULL, inPtr->winTimer);
		inPtr->winTimer = 0;
		gTimers.RemoveItem(inPtr);
	}
	UMemory::Dispose(inRef);
	return;
}
