#include <cstring>
#include <gtest/gtest.h>

#include "../common/UDigest.h"
#include "../common/UMemory.h"

TEST(Digests, MD5)
{
	const char *testString = "Hello, World!";
	byte hash[20] = {0};
	UDigest::MD5_Encode(testString, strlen(testString), hash);
	EXPECT_EQ(
	    true,
	    UMemory::Compare(
	        hash,
	        "\x0a\x0a\x9f\x2a\x67\x72\x94\x25\x57\xab\x53\x55\xd7\x6a\xf4\x42\xf8\xf6\x5e\x01",
	        20));
}
