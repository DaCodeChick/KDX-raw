#include <cstring>
#include <gtest/gtest.h>

#include "../AppWarrior/CTokenizer.h"

TEST(Tokenizer, Default)
{
	char str[] = "Hello, world! This is a test.";
	const char *delimiters = " ,.!?;:\n\t";
	uint size = 0;
	char delim[4] = {0};
	CTokenizer tokenizer(str, std::strlen(str), delimiters);
	for (char *token = (char *)tokenizer.GetNextToken(&size, &delim); token != nullptr;
	     token = (char *)tokenizer.GetNextToken(&size, &delim))
	{
		printf("Size: %u\t, Delimiters: %s\t, Token: %s\n", size, delim, token);
	}
}

TEST(Tokenizer, TrimWhispace)
{
	char str[] = "Hello, world! This is a test.";
	const char *delimiters = " ,.!?;:\n\t";
	uint size = 0;
	char delim[4] = {0};
	CTokenizer tokenizer(str, std::strlen(str), delimiters, 1);
	for (char *token = (char *)tokenizer.GetNextToken(&size, &delim); token != nullptr;
	     token = (char *)tokenizer.GetNextToken(&size, &delim))
	{
		printf("Size: %u\t, Delimiters: %s\t, Token: %s\n", size, delim, token);
	}
}
