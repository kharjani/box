#pragma once
#include "MiniCppUnit.hpp"
#include "RleData.h"
#include <iostream>
#include <iomanip>

// Helper functions
bool buffersAreSame(const char* expected, const char* actual, size_t size);
void runCompressionTest(char* test, size_t testSize,
	char* expected, size_t expectedSize);
void runDecompressionTest(char* test, size_t testSize,
	char* expected, size_t expectedSize);

// IMPORTANT NOTE --
// The tests all use "sizeof" to find the size of the input
// buffer. However, remember that this only works because the
// character arrays are statically allocated.
// If you just have a pointer to a C-style string, "sizeof"
// will return the size of the pointer type (either 4 or 8).
class CompressionTests : public TestFixture<CompressionTests>
{
public:
	TEST_FIXTURE_DESCRIBE(CompressionTests, "Testing Compression...")
	{
		TEST_CASE_DESCRIBE(testBasicPositiveRuns, "Basic positive runs test (compression)");
		// TODO: Add more Compression test cases
        TEST_CASE_DESCRIBE(testBasicNegativeRuns, "Basic negative runs test (compression)");
        TEST_CASE_DESCRIBE(testAlternateRuns, "Alternate runs test (compression)");
        TEST_CASE_DESCRIBE(testLongPositiveRuns, "Long positive runs test (compression)");
        TEST_CASE_DESCRIBE(testLongNegativeRuns, "Long negative runs test (compression)");
        TEST_CASE_DESCRIBE(testLongAlternateRuns, "Long alternate runs test (compression)");
        
        
	}
    
    void testBasicNegativeRuns()
    {
        char test[] =
        "abdcbacdba"
        "cdbacdbacd"
        "bacdbacdba"
        "cdbacdbacd"
        "bacdbacdba"
        "cdbacdbacd"
        "bacdbacdb";
        
        char expected[] = "\xBB" "abdcbacdbacdbacdbacdbacdbacdbacdbacdbacdb"
        "acdbacdbacdbacdbacdbacdbacdb";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
      
    }
    void testLongNegativeRuns()
    {
        char test[] =
        "abdcbacdba"
        "cdbacdbacd"
        "bacdbacdba"
        "cdbacdbacd"
        "bacdbacdba"
        "cdbacdbacd"
        "bacdbacdba"
        "cdbacdbacd"
        "bacdbacdba"
        "cdbacdbacd"
        "bacdbacdba"
        "cdbacdbacd"
        "bacdbac" // counts to 127, 23 chars remaining
        "dba"
        "cdbacdbacd"
        "bacdbacdba"; // total (15*10) = 150 chars
        
        char expected[] = "\x7F" "abdcbacdba"
        "cdbacdbacd"
        "bacdbacdba"
        "cdbacdbacd"
        "bacdbacdba"
        "cdbacdbacd"
        "bacdbacdba"
        "cdbacdbacd"
        "bacdbacdba"
        "cdbacdbacd"
        "bacdbacdba"
        "cdbacdbacd"
        "bacdbac"
        "\xE9"
        "dba"
        "cdbacdbacd"
        "bacdbacdba";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
        
    }
    
    
    void testAlternateRuns()
    {
        char test[] = "aaabbbbbbcccehsbejjjeeenndiqnkkkndaaaaaaarueownwwllldkwwldjjjjbqlaqwertyyyy";
        
        char expected[] = "\x03" "a" "\x06" "b" "\x03" "c" "\xFB" "ehsbe"
        "\x03" "j" "\x03" "e" "\x02" "n" "\xFC" "diqn" "\x03" "k"
        "\xFE" "nd" "\x07" "a" "\xFA" "rueown" "\x02" "ww"
        "\x03" "lll" "\xFE" "dk" "\x02" "ww" "\xFE" "ld" "\x04" "j"
        "\xF7" "bqlaqwert" "\x04" "y";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
        
    }
    
    void testLongAlternateRuns()
    {
        char test[] = "aaabbbbbbcccehsbejjjeeenndiqncccccccccccccccccccccccccccccccccccccccccccccccccc"
        "cccccccccccccccccccccccccccccccccccccccccccccccccc"
        "cccccccccccccccccccccccccccccccccccccccccccccccccckkkndaaaaaaarueownwwllldkwwldjjjjbqlaqwertyyyy";
        
        char expected[] = "\x03" "a" "\x06" "b" "\x03" "c" "\xFB" "ehsbe"
        "\x03" "j" "\x03" "e" "\x02" "n" "\xFC" "diqn" "\x7F" "c" "\x17" "c" "\x03" "k"
        "\xFE" "nd" "\x07" "a" "\xFA" "rueown" "\x02" "ww"
        "\x03" "lll" "\xFE" "dk" "\x02" "ww" "\xFE" "ld" "\x04" "j"
        "\xF7" "bqlaqwert" "\x04" "y";
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
        
    }
    
	
	void testBasicPositiveRuns()
	{
		char test[] = "aaabbbcccdddaaabbbcccdddaaabbbcccdddaaabbbc"
			"ccdddaaabbbcccdddaaabbbcccdddaaabbbcccdddaaabbbcccddd";
		char expected[] = "\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d";
		
		runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
	}
    
    void testLongPositiveRuns()
    {
        char test[] = "cccccccccccccccccccccccccccccccccccccccccccccccccc"
        "cccccccccccccccccccccccccccccccccccccccccccccccccc"
        "cccccccccccccccccccccccccccccccccccccccccccccccccc"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaa"
        "bbbbbbbbbbbbbbbbbbbb";
        
        
        char expected[] = "\x7F" "c" "\x17" "c" "\x7F" "a" "\x2B" "a"
        "\x14" "b"  ;
        
        runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
};

class DecompressionTests : public TestFixture<DecompressionTests>
{
public:
	TEST_FIXTURE_DESCRIBE(DecompressionTests, "Testing Decompression...")
	{
		//TEST_CASE_DESCRIBE(testBasicPositiveRuns, "Basic positive run test");
		// TODO: Add more Decompression test  cases
	}
	
	void testBasicPositiveRuns()
	{
		char test[] = "\x28" "x";
		char expected[] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
		
		runDecompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
	}
};

REGISTER_FIXTURE(CompressionTests);
REGISTER_FIXTURE(DecompressionTests);

bool buffersAreSame(const char* expected, const char* actual, size_t size)
{
	if (actual == nullptr)
	{
		std::cerr << std::endl << "Actual data is null." << std::endl;
		return false;
	}

	bool retVal = true;

	for (size_t i = 0; i < size; i++)
	{
		if (expected[i] != actual[i])
		{
			retVal = false;
			std::cerr << std::endl
				<< "Expected 0x" << std::hex << static_cast<unsigned>(expected[i])
				<< " at index " << std::dec << i << " but saw 0x"
				<< std::hex << static_cast<unsigned>(actual[i]) << std::endl;
			
		}
	}

	return retVal;
}

void runCompressionTest(char* test, size_t testSize, 
	char* expected, size_t expectedSize)
{
	RleData r;
	r.Compress(test, testSize);
	ASSERT_TEST_MESSAGE(buffersAreSame(expected, r.mData, expectedSize),
		"Buffer mismatch (see above for details)");
}

void runDecompressionTest(char* test, size_t testSize,
	char* expected, size_t expectedSize)
{
	RleData r;
	r.Decompress(test, testSize, expectedSize);
	ASSERT_TEST_MESSAGE(buffersAreSame(expected, r.mData, expectedSize),
		"Buffer mismatch (see above for details)");
}
