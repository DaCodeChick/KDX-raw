#pragma once

#include "typedefs.h"

/// @brief Digest utilities for encoding and hashing data.
class EXPORT UDigest
{
public:
	static uint Base64_Encode(const void *inData, uint inDataSize, void *outData);
	static void *Base80_Decode(const void *inData, uint inDataSize, uint *outSize);

	/**
	 * @brief Encodes data using the MD5 hashing algorithm.
	 *
	 * @param inData
	 * @param inDataSize
	 * @param outDigest
	 */
	static void MD5_Encode(const void *inData, uint inDataSize, void *outDigest);
};

/// @brief MD5 hashing algorithm implementation.
class EXPORT _MD5
{
public:
	/**
	 * @brief Clears the MD5 state and prepares it for a new hash computation.
	 *
	 * @param inSize
	 */
	void Clear(uint inSize);

	/// @brief Initializes the MD5 hashing algorithm.
	void Init();

	/**
	 * @brief Reports the current MD5 hash digest.
	 *
	 * @param outDigest
	 */
	void Report(void *outDigest);

	/**
	 * @brief Updates the MD5 hash with new data.
	 *
	 * @param inData
	 * @param inDataSize
	 */
	void Update(const void *inData, uint inDataSize);

private:
	uint mState[5];
	uint mCount;
	byte mBuffer[64];
	uint mBufferLength;

	void Transform(const uint *inBlock);
};
