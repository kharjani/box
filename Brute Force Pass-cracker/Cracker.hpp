//
//  Cracker.hpp
//  password-mac
//
//  Created by Krish on 2/5/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#ifndef Cracker_hpp
#define Cracker_hpp

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include "Timer.h"
#include "Sha1.h"

class Cracker
{
public:
    
    Cracker(std::istream &dictionaryFile, std::istream &passwordFile);
    ~Cracker();
    void buildMap(std::istream &dictionaryFile);
    void decrypt(std::istream& passwordFile, std::unordered_map<std::string, std::string>& dictionary);
    
    struct Password {
        int entry = 0;
        std::string str_pass = "";
        std::string hex_pass = "";
    };
    
    void bruteSolver(std::vector<Password*> &brute, std::map<int, Password*> &solved);
    
    char getChar(int val);
    int getInt(char c);
    void output();
    
    
    
private:
    
    std::unordered_map<std::string, std::string> initialMap;
    // key = hash result, value = actual word
    
    std::vector<Password*> brute; // passwords to be solved by brute force
    std::map<int, Password*> solved; // passwords solved by simple dictionary lookup, stored with their entry #
    
};







#endif /* Cracker_hpp */
