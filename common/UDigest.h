#pragma once

#include "typedefs.h"

/// @brief Digest utilities for encoding and hashing data.
class EXPORT UDigest
{
public:
	/**
	 * @brief Decodes Base64 encoded data.
	 *
	 * @param inData Pointer to the Base64 encoded data.
	 * @param inDataSize Size of the input data.
	 * @param outSize Pointer to a variable that will receive the size of the decoded data.
	 * @return Decoded data pointer.
	 */
	static uint Base64_Encode(const void *inData, uint inDataSize, void *outData);

	/**
	 * @brief Decodes Base80 encoded data.
	 *
	 * @param inData Pointer to the Base80 encoded data.
	 * @param inDataSize Size of the input data.
	 * @param outSize Pointer to a variable that will receive the size of the decoded data.
	 * @return Decoded data pointer.
	 */
	static void *Base80_Decode(const void *inData, uint inDataSize, uint *outSize);

	/**
	 * @brief Encodes data using the MD5 hashing algorithm.
	 *
	 * @param inData Pointer to the input data.
	 * @param inDataSize Size of the input data.
	 * @param outDigest Pointer to a buffer that will receive the MD5 digest.
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
	 * @param outDigest Pointer to a buffer that will receive the MD5 digest.
	 */
	void Report(void *outDigest);

	/**
	 * @brief Updates the MD5 hash with new data.
	 *
	 * @param inData Pointer to the input data.
	 * @param inDataSize Size of the input data.
	 */
	void Update(const void *inData, uint inDataSize);

private:
	uint mState[5];
	uint mCount;
	byte mBuffer[64];
	uint mBufferLength;

	void Transform(const uint *inBlock);
};
