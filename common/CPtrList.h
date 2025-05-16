#pragma once

#include "typedefs.h"

class EXPORT CVoidPtrList
{
public:
	void AddBackItem(void *inPtr);
	void AddFrontItem(void *inPtr);
	void *AddItem(void *inPtr, uint inSize);
	void *AddItem(void *inPtr);
	void *InsertItem(void *inOffset, void *inPtr, uint inSize);
	void *InsertItem(void *inPtr, uint inIndex, byte inFillValue);
	bool IsInList(const void *inPtr) const;
	void *PopFront();
	void *RemoveItem(void *inPtr, uint inSize);
	bool RemoveItem(void *inPtr);

protected:
	void *mHead, *mTail, *mOffset;
	uint mCount;

	void Preallocate(uint inSize, uint inCount);
	void Preallocate(uint inSize);
};