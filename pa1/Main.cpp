// Main.cpp : Defines the entry point for the console application.
//

#include "RleTests.h"
#include "RleData.h"
#include <cstring>
#include <iostream>
#include <string>
#include <sstream>
#include "RLEFile.h"

using namespace std;

void Part1Tests()
{
	TestFixtureFactory::theInstance().runTests();
}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
        
        string s = "abcd";
        cout << sizeof(s) << endl;
        
        int a = 100;
        a = a * -1;
        cout << a << endl;
        
		// Just the tests
		Part1Tests();
	}
	else
	{
		// TODO: Get the file name from argv[1] and either compress/decompress
        string filename;
        cin >> filename;
        cout << "Name: " << filename << endl;
	}
	return 0;
}

