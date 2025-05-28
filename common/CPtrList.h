#pragma once

#include "typedefs.h"

/// @brief A list of pointers to void, allowing for dynamic memory management.
class EXPORT CVoidPtrList
{
public:
	void AddBackItem(void *inPtr);

	/**
	 * @brief Add a pointer to the front of the list.
	 * 
	 * @param inPtr Pointer to the item to add.
	 */
	void AddFrontItem(void *inPtr);
	void *AddItem(void *inPtr, uint inSize);
	void *AddItem(void *inPtr);
	void *InsertItem(void *inOffset, void *inPtr, uint inSize);
	void *InsertItem(void *inPtr, uint inIndex, byte inFillValue);
	bool IsInList(const void *inPtr) const;

	/**
	 * @brief Remove and return the first item from the list.
	 * 
	 * @return Pointer to the removed item, or NULL if the list is empty.
	 */
	void *PopFront();

	/**
	 * @brief Remove an item from the list.
	 * 
	 * @param inPtr Pointer to the item to remove.
	 * @param inSize Size of the item to remove.
	 * @return void* 
	 */
	void *RemoveItem(void *inPtr, uint inSize);

	/**
	 * @brief Remove an item from the list.
	 * 
	 * @param inPtr Pointer to the item to remove.
	 * @return true if the item was removed, false otherwise.
	 */
	bool RemoveItem(void *inPtr);

protected:
	void *mHead, *mTail, *mOffset;
	uint mCount;

	/**
	 * @brief Preallocate memory for the list.
	 * 
	 * @param inSize Size of the items to preallocate.
	 * @param inCount Number of items to preallocate.
	 */
	void Preallocate(uint inSize, uint inCount);

	/**
	 * @brief Preallocate memory for the list.
	 * 
	 * @param inSize Size of the items to preallocate.
	 */
	void Preallocate(uint inSize);
};

/**
 * @brief A list of pointers to a specific type, derived from CVoidPtrList.
 * 
 * @tparam T The type of pointers stored in the list.
 */
template <class T> class CPtrList : public CVoidPtrList
{
public:
	/**
	 * @brief Add a pointer to the end of the list.
	 * 
	 * @param inPtr Pointer to the item to add.
	 */
	void AddBackItem(T *inPtr)
	{
		CVoidPtrList::AddBackItem(inPtr);
	}

	/**
	 * @brief Add a pointer to the front of the list.
	 * 
	 * @param inPtr Pointer to the item to add.
	 */
	void AddFrontItem(T *inPtr)
	{
		CVoidPtrList::AddFrontItem(inPtr);
	}

	/**
	 * @brief Add an item to the list.
	 * 
	 * @param inPtr Pointer to the item to add.
	 * @param inSize Size of the item to add.
	 * @return T* 
	 */
	T *AddItem(T *inPtr, uint inSize)
	{
		return (T *)CVoidPtrList::AddItem(inPtr, inSize);
	}

	/**
	 * @brief Add an item to the list.
	 * 
	 * @param inPtr Pointer to the item to add.
	 * @return T* 
	 */
	T *AddItem(T *inPtr)
	{
		return (T *)CVoidPtrList::AddItem(inPtr);
	}

	/**
	 * @brief Insert an item into the list at a specific offset.
	 * 
	 * @param inOffset Pointer to the offset where the item will be inserted.
	 * @param inPtr Pointer to the item to insert.
	 * @param inSize Size of the item to insert.
	 * @return T* 
	 */
	T *InsertItem(T *inOffset, T *inPtr, uint inSize)
	{
		return (T *)CVoidPtrList::InsertItem(inOffset, inPtr, inSize);
	}

	/**
	 * @brief Insert an item into the list at a specific index.
	 * 
	 * @param inPtr Pointer to the item to insert.
	 * @param inIndex Index at which to insert the item.
	 * @param inFillValue Value to fill if the list needs to grow.
	 * @return T* 
	 */
	T *InsertItem(T *inPtr, uint inIndex, byte inFillValue)
	{
		return (T *)CVoidPtrList::InsertItem(inPtr, inIndex, inFillValue);
	}

	/**
	 * @brief Check if a pointer is in the list.
	 * 
	 * @param inPtr Pointer to check.
	 * @return true if the pointer is in the list, false otherwise.
	 */
	bool IsInList(const T *inPtr) const
	{
		return CVoidPtrList::IsInList(inPtr);
	}

	/**
	 * @brief Remove and return the first item from the list.
	 * 
	 * @return T* Pointer to the removed item, or NULL if the list is empty.
	 */
	T *PopFront()
	{
		return (T *)CVoidPtrList::PopFront();
	}

	/**
	 * @brief Remove an item from the list.
	 * 
	 * @param inPtr Pointer to the item to remove.
	 * @param inSize Size of the item to remove.
	 * @return T* 
	 */
	T *RemoveItem(T *inPtr, uint inSize)
	{
		return (T *)CVoidPtrList::RemoveItem(inPtr, inSize);
	}

	/**
	 * @brief Remove an item from the list.
	 * 
	 * @param inPtr Pointer to the item to remove.
	 * @return true if the item was removed, false otherwise.
	 */
	bool RemoveItem(T *inPtr)
	{
		return CVoidPtrList::RemoveItem(inPtr);
	}
};