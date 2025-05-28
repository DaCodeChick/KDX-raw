#pragma once

#include "typedefs.h"

typedef void (*TCryptProc)(void *ioData, bool isDecrypt);

/// @brief Class for cryptographic transactions.
class EXPORT UCryptTransact
{
public:
	static void BlockCrypt6E7DFD34(void *ioData, bool inIsDecrypt);

	/**
	 * @brief Generates a key based on the provided data.
	 *
	 * @param inData Pointer to the input data used for key generation.
	 * @param inDataSize Size of the input data.
	 * @param outData Pointer to the output buffer where the generated key will be stored.
	 */
	static void GenerateKey(const void *inData, uint inDataSize, void *outData);

	/**
	 * @brief Checks if the provided data is a default key.
	 *
	 * @param inData Pointer to the data to be checked.
	 * @return true if the data is a default key, false otherwise.
	 */
	static bool IsDefaultKey(const void *inData);

	/**
	 * @brief Encrypts or decrypts data using a specific key.
	 *
	 * @param inInit Initialization vector for the encryption/decryption.
	 * @param ioData Pointer to the data to be encrypted or decrypted.
	 * @param inDataSize Size of the data to be processed.
	 */
	static void TCPPacketCrypt(uint inInit, void *ioData, uint inDataSize);
};
