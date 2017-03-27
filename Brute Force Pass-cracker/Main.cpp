// Main.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <string>
#include "Sha1.h"
#include "Cracker.hpp"
#include <fstream>

//using namespace std;

int main(int argc, char* argv[])
{
    if (argc == 2)
    {
//        int num = 48;
//        std::cout << (char)num << std::endl;
//        std::string s = "abcd";
        //std::cout << sizeof(s) << std::endl;
        
        
        
//        std::string word;
//        std::cin >> word;
//        std::cout << word << "  " << word.size() << std::endl;
        std::string word = argv[1];
       
        
        
        unsigned char hash[20];
        sha1::calc(word.c_str(), word.size(), hash);
        
        
        
        char hex_str[41];
        sha1::toHexString(hash, hex_str);
        for (int i = 0; i < 40; i++) {
            std::cout << hex_str[i];
        }
        std::cout << std::endl;
        
    }
    else if (argc == 3)
    {
        std::ifstream dictionaryFile(argv[1]); // read in files
        std::ifstream passwordFile(argv[2]);
        if (dictionaryFile.good() && passwordFile.good()) // check if files exist/are good
        {
            Cracker(dictionaryFile, passwordFile);
        }
        else
        {
            std::cout << "file invalid soz";
        }
        
    }
    
    
	return 0;
}

