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

template <class T> class CPtrList : public CVoidPtrList
{
public:
	void AddBackItem(T *inPtr)
	{
		CVoidPtrList::AddBackItem(inPtr);
	}
	void AddFrontItem(T *inPtr)
	{
		CVoidPtrList::AddFrontItem(inPtr);
	}
	T *AddItem(T *inPtr, uint inSize)
	{
		return (T *)CVoidPtrList::AddItem(inPtr, inSize);
	}
	T *AddItem(T *inPtr)
	{
		return (T *)CVoidPtrList::AddItem(inPtr);
	}
	T *InsertItem(T *inOffset, T *inPtr, uint inSize)
	{
		return (T *)CVoidPtrList::InsertItem(inOffset, inPtr, inSize);
	}
	T *InsertItem(T *inPtr, uint inIndex, byte inFillValue)
	{
		return (T *)CVoidPtrList::InsertItem(inPtr, inIndex, inFillValue);
	}
	bool IsInList(const T *inPtr) const
	{
		return CVoidPtrList::IsInList(inPtr);
	}
	T *PopFront()
	{
		return (T *)CVoidPtrList::PopFront();
	}
	T *RemoveItem(T *inPtr, uint inSize)
	{
		return (T *)CVoidPtrList::RemoveItem(inPtr, inSize);
	}
	bool RemoveItem(T *inPtr)
	{
		return CVoidPtrList::RemoveItem(inPtr);
	}
};