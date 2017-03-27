//
//  Cracker.cpp
//  password-mac
//
//  Created by Krish on 2/5/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Cracker.hpp"
#include <iostream>


Cracker::Cracker(std::istream &dictionaryFile, std::istream &passwordFile)
{
    buildMap(dictionaryFile);
    //lookUp(passwordFile, initialMap);
}


void Cracker::buildMap(std::istream &dictionaryFile)
{
    Timer timer;
    timer.start();
    
    std::string word = "";
    
    
    initialMap.rehash(100000);
    
    while (getline(dictionaryFile, word))
    {
        unsigned char hash[20];
        sha1::calc(word.c_str(), word.size(), hash);
        
        //std::cout << "word is: " << word << " size: " << word.size() << std::endl;
        char hex[41];
        sha1::toHexString(hash, hex);
        
        
        std::string key(hex); // convert back to string
        initialMap[key] = word; // assign key the actual word
    }
    
    //not sure if double or float, assignment instructions are confusing
    float fElapsed = timer.getElapsed();
    
    std::cout << "initial map build time elapsed: " << fElapsed << std::endl;
}

void Cracker::decrypt(std::istream& passwordFile, std::unordered_map<std::string, std::string>& dictionary)
{
    std::string key = "";
    int passCounter = 0; // will hold entry number according to input file
    Timer timer;
    timer.start();
    while (getline(passwordFile, key))
    {
        
        
        //
        Password *curr = new Password();
        curr->entry = passCounter;
        curr->hex_pass = key;
        
        std::unordered_map<std::string, std::string>::iterator it;
        it = dictionary.find(key);
        
        
        
        if (it == dictionary.end()) // no results found
        {
            brute.push_back(curr);
        }
        else // found a match
        {
            
            curr->str_pass = it->second; // plain text password from dictionary
            
            solved.insert(std::make_pair(passCounter, curr));
        }
        passCounter++;
        //printResult(key, password, ofile);
    }
    float fElapsed = timer.getElapsed();
    std::cout << "dictionary decrypt time elapsed: " << fElapsed <<  std::endl;
    
    // call brute force on the rest of the passwords
    
    Timer bruteTimer;
    bruteTimer.start();
    bruteSolver(brute, solved);
    
    float fBruteElapsed = bruteTimer.getElapsed();
    std::cout << "brute force time elapsed: " << fBruteElapsed <<  std::endl;
    
    
}

void Cracker::bruteSolver(std::vector<Password*> &brute, std::map<int,Password*> &solved)
{
    // need to organize it so it can start and stop from a certain point
    // lambda expressions????????????????
    
    
    std::string guess;
    for(int j = 0; j < brute.size(); j++) // for every value in brute vector
    {
        
    
        int machine[4] = {-1,-1,-1,-1}; // start with no values at all
        // 0 = 'a', .... 25 = 'z' .... 35 = '9'
        bool done = false;
        bool matchFound = false;
        
        while(!done)
        {
            if(machine[3] < 35) // then increment machine[3]
            {
                machine[3]++;
            }
            else
            {
                // 4th digit is at 35, need to carry
                if(machine[2] < 35)
                {
                    machine[2]++;
                    machine[3] = 0;
                }
                else
                {
                    // 4th and 3rd digits are at 35, need to carry further
                    if(machine[1] < 35)
                    {
                        machine[1]++;
                        machine[2] = 0;
                        machine[3] = 0;
                    }
                    else
                    {
                        if(machine[0] < 35)
                        {
                            machine[0]++;
                            machine[1] = 0;
                            machine[2] = 0;
                            machine[3] = 0;
                        }
                        else // all digits at 35, we're done
                        {
                            done = true;
                        }
                    }
                }
            }
            guess = "";
            for(int i=0; i < 4; i++)
            {
                if(machine[i] == -1)continue; // -1 means its not included
                char c = getChar(machine[i]);
                guess+= c;
            }
            
            unsigned char hash[20];
            sha1::calc(guess.c_str(), guess.size(), hash);
            
            char hex_str[41];
            sha1::toHexString(hash, hex_str);
            
            if(hex_str == brute.at(j)->hex_pass)
            {
                // we got a match
                matchFound = true;
                done = true;
            }
        }
        
        brute.at(j)->str_pass = guess;
        
    }
    output(); // create output file
    return;
}

char Cracker::getChar(int num)
{
    // corresponding numbers from ascii table
    if (num >= 0 && num <= 25)
	{
        return (num + 97);
	}
	
    else
	{
        return (num + 22);
	}
}

void Cracker::output() // build output txt file
{
	std::ofstream outputFile("pass_solved.txt");
    
    for(const auto& pass : solved)
    {
        if(pass.second->str_pass.empty())
        {
            // hasn't been solved
            outputFile << pass.second->hex_pass << ", ??" << "\n";
        }
        else{
            // we have the cracked password
            outputFile << pass.second->hex_pass << ", " << pass.second->str_pass << "\n";
        }
    }
    outputFile.close();
        
    


}


Cracker::~Cracker()
{
}
