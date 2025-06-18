#include <cstring>
#include <gtest/gtest.h>

#include "../AppWarrior/UMemory.h"

TEST(Checksums, Adler)
{
	const char *testString = "Hello, World!";
	uint checksum = UMemory::AdlerSum(testString, std::strlen(testString), 0xDEADBEEF);
	EXPECT_EQ(checksum, 0xB0F7C358);
}

TEST(Checksums, CRC)
{
	const char *testString = "Hello, World!";
	uint checksum = UMemory::CRC(testString, std::strlen(testString), 0xDEADBEEF);
	EXPECT_EQ(checksum, 0x441CBA41);
}

TEST(Checksums, FNV1a)
{
	const char *testString = "Hello, World!";
	uint checksum = UMemory::Checksum(testString, std::strlen(testString), 0xDEADBEEF);
	EXPECT_EQ(checksum, 0x4CB54FE4);
}