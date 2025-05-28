#pragma once

#include "typedefs.h"

/// @brief Twofish encryption algorithm implementation.
class EXPORT CTwofish
{
public:
	/**
	 * @brief Constructor for the CTwofish class.
	 * 
	 * @param inData Pointer to the key data used for encryption.
	 */
	CTwofish(const void *inData);

	/**
	 * @brief Encrypts the given data using the Twofish algorithm.
	 * 
	 * @param inData Pointer to the input data to be encrypted.
	 * @param outData Pointer to the output buffer where the encrypted data will be stored.
	 */
	void Encrypt(const void *inData, void *outData);

	/**
	 * @brief Encrypts data in CBC (Cipher Block Chaining) mode.
	 * 
	 * @param outData Pointer to the output buffer where the encrypted data will be stored.
	 * @param ioPartialBlockSize Pointer to the size of the partial block. This will be updated with the size of the last block processed.
	 * @param inData Pointer to the input data to be encrypted.
	 * @param inDataSize Size of the input data to be encrypted.
	 */
	void EncryptCBC(void *outData, uint *ioPartialBlockSize, const void *inData, uint inDataSize);

private:
	uint mSBox[4][256];
	uint mKey[40];

	void EncryptCBCIteration(const void *inData, void *outData);
};