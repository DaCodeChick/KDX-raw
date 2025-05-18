#include <cstring>
#include <gtest/gtest.h>

#include "../common/UCryptTransact.h"
#include "../common/UDigest.h"
#include "../common/UMemory.h"

TEST(Crypt, GenerateKey)
{
	const char *testString = "Hello, World!";
	byte hash[32] = {0};
	UCryptTransact::GenerateKey(testString, strlen(testString), hash);
	EXPECT_EQ(true,
	          UMemory::Compare(hash,
	                           "\x0a\x0a\x9f\x2a\x67\x72\x94\x25\x57\xab\x53\x55\xd7\x6a\xf4\x42"
	                           "\xf8\xf6\x5e\x01\x0a\x0a\x9f\x2a\x67\x72\x94\x25\x68\x7e\x59\xd2",
	                           32));
}
