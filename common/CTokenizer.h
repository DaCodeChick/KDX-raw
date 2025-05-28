#pragma once

#include "typedefs.h"

/// @brief Tokenizer class for parsing strings based on delimiters.
class EXPORT CTokenizer
{
public:
	/**
	 * @brief Constructs a tokenizer with the specified parameters.
	 *
	 * @param inOffset
	 * @param inSize
	 * @param inDelimiters
	 * @param inOptions
	 */
	CTokenizer(void *inOffset, uint inSize, const void *inDelimiters, uint inOptions = 0);

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
