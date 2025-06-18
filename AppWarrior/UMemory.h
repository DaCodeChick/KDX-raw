#pragma once

#include "typedefs.h"

#ifdef _WIN32
/// @brief Handle type for memory blocks.
typedef HGLOBAL THdl;
#else
#include <cstdlib>

/// @brief Handle type for memory blocks.
typedef class THdlObj *THdl;
#endif // _WIN32

/// @brief Memory utility class.
class EXPORT UMemory
{
public:
	/**
	 * @brief Computes the Adler-32 checksum of the given data.
	 *
	 * @param inData Pointer to the data to compute the checksum for.
	 * @param inDataSize Size of the data in bytes.
	 * @param inInit Initial value for the checksum.
	 * @return The computed Adler-32 checksum.
	 */
	static uint AdlerSum(const void *inData, uint inDataSize, uint inInit);

	/**
	 * @brief Computes the checksum of the given data.
	 *
	 * @param inData Pointer to the data to compute the checksum for.
	 * @param inDataSize Size of the data in bytes.
	 * @param inInit Initial value for the checksum.
	 * @return The computed checksum.
	 */
	static uint Checksum(const void *inData, uint inDataSize, uint inInit);

	/**
	 * @brief Clears a block of memory.
	 *
	 * @param outDest Pointer to the destination memory block.
	 * @param inSize Size of the memory block to clear in bytes.
	 */
	static void Clear(void *outDest, uint inSize);

	/**
	 * @brief Compares two blocks of memory.
	 *
	 * @param inDataA Pointer to the first block of memory.
	 * @param inDataB Pointer to the second block of memory.
	 * @param inSize Size of the memory blocks to compare in bytes.
	 * @return True if the blocks are equal, false otherwise.
	 */
	static bool Compare(const void *inDataA, const void *inDataB, uint inSize);

	/**
	 * @brief Computes the CRC (Cyclic Redundancy Check) of the given data.
	 *
	 * @param inData Pointer to the data to compute the CRC for.
	 * @param inDataSize Size of the data in bytes.
	 * @param inInit Initial value for the CRC.
	 * @return The computed CRC value.
	 */
	static uint CRC(const void *inData, uint inDataSize, uint inInit);

	/**
	 * @brief Disposes of a memory handle.
	 *
	 * @param inHdl Handle to the memory block to dispose of.
	 */
	static void Dispose(THdl inHdl);

	/**
	 * @brief Fills a block of memory with a specified byte, word, or long value.
	 *
	 * @param outDest Pointer to the destination memory block.
	 * @param inSize Size of the memory block to fill in bytes.
	 * @param inByte Byte value to fill the memory block with.
	 */
	static void Fill(void *outDest, uint inSize, byte inByte);

	/**
	 * @brief Fills a block of memory with a specified word value.
	 *
	 * @param outDest Pointer to the destination memory block.
	 * @param inSize Size of the memory block to fill in bytes.
	 * @param inWord Word value to fill the memory block with.
	 */
	static void Fill(void *outDest, uint inSize, ushort inWord);

	/**
	 * @brief Fills a block of memory with a specified long value.
	 *
	 * @param outDest Pointer to the destination memory block.
	 * @param inSize Size of the memory block to fill in bytes.
	 * @param inLong Long value to fill the memory block with.
	 */
	static void Fill(void *outDest, uint inSize, uint inLong);

	static longlong GetBlockCount(uint *outCount);

	/**
	 * @brief Locks a memory handle to access its data.
	 *
	 * @param inHdl Handle to the memory block to lock.
	 * @return Pointer to the locked memory block.
	 */
	static void *Lock(THdl inHdl)
	{
#ifdef _WIN32
		return GlobalLock(inHdl);
#else
		return *inHdl;
#endif // _WIN32
	}

	/**
	 * @brief Moves a block of memory from one location to another.
	 *
	 * @param outDest Pointer to the destination memory block.
	 * @param inSrc Pointer to the source memory block.
	 * @param inSize Size of the memory block to move in bytes.
	 * @return The size of the moved memory block.
	 */
	static uint Move(void *outDest, const void *inSrc, uint inSize);

	/**
	 * @brief Creates a new memory handle with the specified size.
	 *
	 * @param inSize Size of the memory block to create in bytes.
	 * @return A handle to the newly created memory block.
	 */
	static THdl NewHandle(uint inSize);

	/**
	 * @brief Creates a new memory handle with the specified data and size.
	 *
	 * @param inData Pointer to the data to initialize the memory block with.
	 * @param inSize Size of the memory block to create in bytes.
	 * @return A handle to the newly created memory block initialized with the data.
	 */
	static THdl NewHandle(const void *inData, uint inSize);

	/**
	 * @brief Creates a new memory handle with the specified size and clears it.
	 *
	 * @param inSize Size of the memory block to create in bytes.
	 * @return A handle to the newly created memory block, cleared to zero.
	 */
	static THdl NewHandleClear(uint inSize);

	/**
	 * @brief Reallocates a memory handle to a new size.
	 *
	 * @param inHdl Handle to the memory block to reallocate.
	 * @param inSize New size for the memory block in bytes.
	 * @return A handle to the reallocated memory block.
	 */
	static THdl Reallocate(THdl inHdl, uint inSize);

	/**
	 * @brief Searches for a block of memory within another block of memory.
	 *
	 * @param inSearchData Pointer to the data to search for.
	 * @param inSearchSize Size of the search data in bytes.
	 * @param inData Pointer to the block of memory to search in.
	 * @param inDataSize Size of the memory block to search in bytes.
	 * @return Pointer to the first occurrence of the search data in the memory block, or nullptr if
	 * not found.
	 */
	static void *Search(const void *inSearchData, uint inSearchSize, const void *inData,
	                    uint inDataSize);

	/**
	 * @brief Searches for a byte in a block of memory.
	 *
	 * @param inByte The byte value to search for.
	 * @param inData Pointer to the block of memory to search in.
	 * @param inSize Size of the memory block to search in bytes.
	 * @return Pointer to the first occurrence of the byte in the memory block, or nullptr if not
	 * found.
	 */
	static byte *SearchByte(byte inByte, const void *inData, uint inSize);

	/**
	 * @brief Searches for a byte in a block of memory, starting from the end and moving backwards.
	 *
	 * @param inByte The byte value to search for.
	 * @param inData Pointer to the block of memory to search in.
	 * @param inSize Size of the memory block to search in bytes.
	 * @return Pointer to the last occurrence of the byte in the memory block, or nullptr if not
	 * found.
	 */
	static byte *SearchByteBackwards(byte inByte, const void *inData, uint inSize);

	/**
	 * @brief Unlocks a memory handle to release access to its data.
	 *
	 * @param inHdl Handle to the memory block to unlock.
	 */
	static void Unlock(THdl inHdl)
	{
#ifdef _WIN32
		GlobalUnlock(inHdl);
#endif // _WIN32
	}
};

/// @brief RAII-style memory handle locker.
class EXPORT StHandleLocker
{
public:
	/**
	 * @brief Constructs a handle locker that locks the specified memory handle.
	 *
	 * @param inHdl Handle to the memory block to lock.
	 * @param outPtr Reference to a pointer that will be set to the locked memory block.
	 */
	StHandleLocker(THdl inHdl, void *&outPtr) : mHdl(inHdl)
	{
		outPtr = UMemory::Lock(mHdl);
	}

	/// @brief Destroys the handle locker and unlocks the memory block.
	~StHandleLocker()
	{
		UMemory::Unlock(mHdl);
	}

private:
	THdl mHdl;
};

#ifndef _WIN32
/// @brief RAII-style memory handle wrapper.
class THdlObj
{
public:
	/**
	 * @brief Constructs a handle object with the specified size.
	 *
	 * @param inSize Size of the memory block to create in bytes.
	 */
	THdlObj(uint inSize) : mHdl(std::malloc(inSize)), mSize(inSize)
	{
	}

	/**
	 * @brief Constructs a handle object with the specified data and size.
	 *
	 * @param inData Pointer to the data to initialize the memory block with.
	 * @param inSize Size of the memory block to create in bytes.
	 */
	THdlObj(const void *inData, uint inSize) : mHdl(std::malloc(inSize)), mSize(inSize)
	{
		if (mHdl)
			UMemory::Move(mHdl, inData, inSize);
	}

	/// @brief Destroys the handle object and frees the memory block.
	~THdlObj()
	{
		std::free(mHdl);
	}

	/// @brief Returns a pointer to the memory block.
	operator*()
	{
		return mHdl;
	}

private:
	void *mHdl;
	uint mSize;
};
#endif // _WIN32
