#pragma once

#include "typedefs.h"

class EXPORT CTokenizer
{
public:
	CTokenizer(void *inOffset, uint inSize, const void *inDelimiters, uint inOptions);
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
