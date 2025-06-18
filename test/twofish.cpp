#include <cstring>
#include <gtest/gtest.h>

#include "../AppWarrior/CTwofish.h"
#include "../AppWarrior/UCryptTransact.h"
#include "../AppWarrior/UMemory.h"

TEST(Twofish, EncryptCBC)
{
	const char *testString = "Hello, World!";
	byte hash[32] = {0};
	UCryptTransact::GenerateKey(testString, strlen(testString), hash);
	CTwofish twofish(hash);
	uint size = 0;
	const char *testData = "This is a test string for Twofish encryption.";
	byte encrypted[64] = {0};
	twofish.EncryptCBC(encrypted, &size, testData, std::strlen(testData));
	for (size_t i = 0; i < std::strlen(testData); ++i)
	{
		printf("\\x%02x", encrypted[i]);
	}
	EXPECT_EQ(true, UMemory::Compare(encrypted,
	                                 "\x90\xe2\x12\xee\xde\x00\x00\x00\xd6\xd9\x68\x61\xd7\x6f\xdf"
	                                 "\x5d\xf1\xf2\x1d\xa5\x80\x7e\xc1\x5d\x16\x05\xc5\x54\x38\x56"
	                                 "\x45\x68\x68\x20\x65\x6e\x63\x72\x79\x70\x74\x69\x6f\x6e\x2e",
	                                 std::strlen(testData)));
}
