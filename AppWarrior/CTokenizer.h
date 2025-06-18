#pragma once

#include "typedefs.h"

/// @brief Tokenizer class for parsing strings based on delimiters.
class EXPORT CTokenizer
{
public:
	/**
	 * @brief Constructs a tokenizer with the specified parameters.
	 *
	 * @param inOffset Pointer to the start of the input string.
	 * @param inSize Size of the input string.
	 * @param inDelimiters Pointer to a string containing delimiter characters.
	 * @param inOptions Options for tokenizer behavior.
	 */
	CTokenizer(void *inOffset, uint inSize, const void *inDelimiters, uint inOptions = 0);

	/**
	 * @brief Retrieves the next token from the input string.
	 *
	 * @param outSize Pointer to a variable that will receive the size of the token.
	 * @param outDelimiter Pointer to a variable that will receive the delimiter used.
	 * @return Pointer to the next token, or NULL if no more tokens are available.
	 */
	void *GetNextToken(uint *outSize, void *outDelimiter);

private:
	typedef void *(CTokenizer::*GetNextTokenProc)(uint *outSize, void *outDelimiter);

	GetNextTokenProc mGetNextTokenProc;
	byte *mOffset, *mEnd;
	uint mFlags;
	uint mPos;
	uint mDelimiterBits[7];

	void *GetNextTokenDefault(uint *outSize, void *outDelimiter);
	void *GetNextTokenWithDelimiters(uint *outSize, void *outDelimiter);
	void *GetNextTokenTrimWhitespace(uint *outSize, void *outDelimiter);
};
