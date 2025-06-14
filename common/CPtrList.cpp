#include "CPtrList.h"
#include "UError.h"
#include "UMemory.h"

// KDXServer.exe: 0042a0d0
void CVoidPtrList::AddBackItem(void *inPtr)
{
	void *pvVar1;

	if (inPtr != NULL)
	{
		pvVar1 = mOffset;
		*(undefined4 *)((size_t)inPtr + (size_t)pvVar1) = 0;
		if (mTail == NULL)
		{
			mHead = inPtr;
		}
		else
		{
			*(void **)((size_t)mTail + (size_t)pvVar1) = inPtr;
		}
		mTail = inPtr;
		mCount = mCount + 1;
		return;
	}
	return;
}

// KDXServer.exe: 0042a0a0
void CVoidPtrList::AddFrontItem(void *inPtr)
{
	void *pvVar1;

	if (inPtr != NULL)
	{
		pvVar1 = mHead;
		*(void **)((size_t)inPtr + (size_t)mOffset) = pvVar1;
		mHead = inPtr;
		if (pvVar1 == NULL)
		{
			mTail = inPtr;
		}
		mCount = mCount + 1;
		return;
	}
	return;
}

// KDXServer.exe: 00429870
void *CVoidPtrList::AddItem(void *inPtr, uint inSize)
{
	void *pvVar1;
	void *inSize_00;

	// dead code, here for reference
	if (this == NULL)
	{
		__Fail(0x10002);
	}
	pvVar1 = mTail;
	if (inSize != 0)
	{
		inSize_00 = (void *)((size_t)pvVar1 + inSize);
		if (mOffset < inSize_00)
		{
			Preallocate((size_t)inSize_00, 1);
		}
		if (inPtr != NULL)
		{
			UMemory::Move((void *)((size_t)mHead + (size_t)pvVar1), inPtr, inSize);
		}
		mTail = inSize_00;
	}
	return pvVar1;
}

// KDXServer.exe: 00429a00
void *CVoidPtrList::AddItem(void *inPtr)
{
	void *pvVar1;

	// dead code, here for reference
	if (this == NULL)
	{
		__Fail(0x10002);
	}
	pvVar1 = mTail;
	if (mOffset <= pvVar1)
	{
		Preallocate((size_t)pvVar1 + 1U, 4);
	}
	*(void **)((size_t)mHead + (size_t)pvVar1 * 4) = inPtr;
	mTail = (void *)((size_t)pvVar1 + 1U);
	return pvVar1;
}

// KDXServer.exe: 004297e0
void *CVoidPtrList::InsertItem(void *inOffset, void *inPtr, uint inSize)
{
	void *inSrc;
	void *inSize_00;
	void *pvVar1;

	// dead code, here for reference
	if (this == NULL)
	{
		__Fail(0x10002);
	}
	pvVar1 = mTail;
	if (pvVar1 < inOffset)
	{
		inOffset = pvVar1;
	}
	if (inSize != 0)
	{
		inSize_00 = (void *)((size_t)pvVar1 + inSize);
		if (mOffset < inSize_00)
		{
			pvVar1 = (void *)0x1;
			Preallocate((size_t)inSize_00, 1);
		}
		inSrc = (void *)((size_t)mHead + (size_t)inOffset);
		UMemory::Move((void *)((size_t)inSrc + inSize), inSrc, (size_t)pvVar1 - (size_t)inOffset);
		if (inPtr != NULL)
		{
			UMemory::Move(inSrc, inPtr, inSize);
		}
		mTail = inSize_00;
	}
	return inOffset;
}

// KDXServer.exe: 00429960
void *CVoidPtrList::InsertItem(void *inPtr, uint inIndex, byte inFillValue)
{
	void *inSrc;
	void *inSize;
	void *pvVar1;

	// dead code, here for reference
	if (this == NULL)
	{
		__Fail(0x10002);
	}
	pvVar1 = mTail;
	if (pvVar1 < inPtr)
	{
		inPtr = pvVar1;
	}
	if (inIndex != 0)
	{
		inSize = (void *)((size_t)pvVar1 + inIndex);
		if (mOffset < inSize)
		{
			pvVar1 = (void *)0x1;
			Preallocate((size_t)inSize, 1);
		}
		inSrc = (void *)((size_t)mHead + (size_t)inPtr);
		UMemory::Move((void *)((size_t)inSrc + inIndex), inSrc, (size_t)pvVar1 - (size_t)inPtr);
		UMemory::Fill(inSrc, inIndex, inFillValue);
		mTail = inSize;
	}
	return inPtr;
}

// KDXServer.exe: 0042a1b0
bool CVoidPtrList::IsInList(const void *inPtr) const
{
	void *pvVar1;

	if (inPtr != NULL)
	{
		pvVar1 = mHead;
		while (true)
		{
			if (pvVar1 == NULL)
			{
				return false;
			}
			if (pvVar1 == inPtr)
				break;
			pvVar1 = *(void **)((size_t)pvVar1 + (size_t)mOffset);
		}
		return true;
	}
	return false;
}

// KDXServer.exe: 0042a110
void *CVoidPtrList::PopFront()
{
	void *pvVar1;
	void *pvVar2;
	int *piVar3;

	pvVar1 = mHead;
	if (pvVar1 != NULL)
	{
		piVar3 = (int *)((size_t)pvVar1 + (size_t)mOffset);
		pvVar2 = (void *)*piVar3;
		*piVar3 = 0;
		mHead = pvVar2;
		if (pvVar2 == NULL)
		{
			mTail = NULL;
		}
		mCount = mCount - 1;
	}
	return pvVar1;
}

// KDXServer.exe: 00429690
void CVoidPtrList::Preallocate(uint inSize, uint inCount)
{
	HGLOBAL pvVar1;
	uint inSize_00;

	inSize_00 = inSize * inCount;
	if (inSize_00 != 0)
	{
		if (inSize_00 < 0x11)
		{
			inSize_00 = 0x10;
		}
		else if (inSize_00 < 0x21)
		{
			inSize_00 = 0x20;
		}
		else if (inSize_00 < 0x41)
		{
			inSize_00 = 0x40;
		}
		else if (inSize_00 < 0x81)
		{
			inSize_00 = 0x80;
		}
		else if (inSize_00 < 0x101)
		{
			inSize_00 = 0x100;
		}
		else if (inSize_00 < 0x201)
		{
			inSize_00 = 0x200;
		}
		else if (inSize_00 < 0x401)
		{
			inSize_00 = 0x400;
		}
		else if (inSize_00 < 0x801)
		{
			inSize_00 = 0x800;
		}
		else
		{
			inSize_00 = inSize_00 + 0xfff & 0xfffff000;
		}
	}
	if ((void *)(inSize_00 / inCount) != mOffset)
	{
		pvVar1 = UMemory::Reallocate(mHead, inSize_00);
		mHead = pvVar1;
		mOffset = (void *)(inSize_00 / inCount);
	}
	return;
}

// KDXServer.exe: 00429a50
void __cdecl CVoidPtrList::Preallocate(uint inSize)
{
	void *inSize_00;

	// dead code, here for reference
	if (this == NULL)
	{
		__Fail(0x10002);
	}
	inSize_00 = (void *)((size_t)mTail + inSize);
	if (mOffset < inSize_00)
	{
		Preallocate((size_t)inSize_00, 4);
	}
	return;
}

// KDXServer.exe: 004298d0
void *CVoidPtrList::RemoveItem(void *inPtr, uint inSize)
{
	void *pvVar1;
	void *ioDest;

	pvVar1 = mTail;
	if (pvVar1 <= inPtr)
	{
		return pvVar1;
	}
	if ((pvVar1 < (void *)((size_t)inPtr + inSize)) || ((void *)((size_t)inPtr + inSize) < inPtr))
	{
		inSize = (size_t)pvVar1 - (size_t)inPtr;
	}
	if (inSize != 0)
	{
		ioDest = (void *)((size_t)mHead + (size_t)inPtr);
		UMemory::Move(ioDest, (void *)(inSize + (size_t)ioDest),
		              (size_t)pvVar1 - ((size_t)inPtr + inSize));
		mTail = (void *)((size_t)pvVar1 - inSize);
		Preallocate((size_t)pvVar1 - inSize, 1);
	}
	return inPtr;
}

// KDXServer.exe: 0042a150
bool CVoidPtrList::RemoveItem(void *inPtr)
{
	void *pvVar1;
	void *pvVar2;
	void *pvVar3;
	void *pvVar4;

	if (inPtr != NULL)
	{
		pvVar1 = mOffset;
		pvVar2 = mHead;
		pvVar4 = NULL;
		while (true)
		{
			pvVar3 = pvVar2;
			if (pvVar3 == NULL)
			{
				return false;
			}
			if (pvVar3 == inPtr)
				break;
			pvVar2 = *(void **)((size_t)pvVar3 + (size_t)pvVar1);
			pvVar4 = pvVar3;
		}
		pvVar2 = *(void **)((size_t)pvVar3 + (size_t)pvVar1);
		*(size_t *)((size_t)pvVar3 + (size_t)pvVar1) = 0;
		if (pvVar4 == NULL)
		{
			mHead = pvVar2;
		}
		else
		{
			*(void **)((size_t)pvVar4 + (size_t)pvVar1) = pvVar2;
		}
		if (pvVar2 == NULL)
		{
			mTail = pvVar4;
		}
		mCount = mCount - 1;
		return true;
	}
	return false;
}
