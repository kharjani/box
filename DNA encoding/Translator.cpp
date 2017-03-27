//
//  Translator.cpp
//  dnawx-mac
//
//  Created by Krish on 3/6/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Translator.hpp"

Translator::Translator(std::string &s)
{
    ReadSequence(s);
    
    
}

void Translator::ReadSequence(const std::string &sequence)
{
//    std::cout << sequence << std::endl;
//    std::cout << "----BREAK----" << std::endl;
    int row = 0;
    bool started = false;
    for(int i=0 ; i < sequence.size(); ++i)
    {
        // regular int describes row num to go to
        
        // ascii from 65 to 90 means its a letter/amino
        
    
        
        if(started)
        {
            if(mStateMachine[row][GetIndex(sequence[i])] < 65)
            {
                
                // statemachine val is a regular int, proceed
                row = mStateMachine[row][GetIndex(sequence[i])];
                if(row == 0) started = false; // stop codon
                continue;
                
            }
            else{
                // its a char (amino acid), so increment in map
                mAminoCount[(char)mStateMachine[row][GetIndex(sequence[i])]]++;
                mTotalCount++;
                row = 3; // check for next amino acid
                //std::cout << "found: " << sequence[i-2] << sequence[i-1] << sequence[i] << std::endl;
                
            }
            
        }
        else{
            // we have not started yet
            // statemachine is on either row 0, 1, or 2
            if(mStateMachine[row][GetIndex(sequence[i])] != 77 )
            {
                row = mStateMachine[row][GetIndex(sequence[i])];
                continue;
            }
            else{
                // we've hit the starting codon
                started = true;
                //std::cout << sequence.substr(0,i) << std::endl;
                mAminoCount[(char)'M']++;
                mTotalCount++;
                row++;
            }
        }
        
    
    }
    
//    for ( auto it = mAminoCount.begin(); it != mAminoCount.end(); ++it )
//        std::cout << "amino:" << it->first << ": " << it->second << std::endl;
}

int Translator::GetIndex(const char c)const
{
    switch(c)
    {
        case 'T':
            return 0;
        case 'C':
            return 1;
        case 'A':
            return 2;
        default:
            return 3;
    }
    
}

std::unordered_map<char, int> Translator::GetAminoMap()
{
    return mAminoCount;
}

int Translator::GetTotalCount() const
{
    return mTotalCount;
}



