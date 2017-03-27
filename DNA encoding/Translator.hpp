//
//  Translator.hpp
//  dnawx-mac
//
//  Created by Krish on 3/6/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#ifndef Translator_hpp
#define Translator_hpp

#include <iostream>
#include <stdio.h>
#include <unordered_map>

class Translator
{
public:
    Translator(std::string &s);
    
    void ReadSequence(const std::string &sequence);
    
    int GetIndex(const char c) const;
    
    std::unordered_map<char, int> GetAminoMap();
    
    int GetTotalCount() const;
    
private:
    
    int mTotalCount = 0;
    
    std::unordered_map<char,int> mAminoCount = {
        {'F', 0},
        {'S', 0},
        {'Y', 0},
        {'T', 0},
        {'C', 0},
        {'W', 0},
        {'L', 0},
        {'P', 0},
        {'Q', 0},
        {'R', 0},
        {'H', 0},
        {'I', 0},
        {'N', 0},
        {'K', 0},
        {'M', 0},
        {'A', 0},
        {'V', 0},
        {'D', 0},
        {'E', 0}
    
    };
    
    int mStateMachine[24][4] =
    {
        // if you hit a number, go to that state/row number
        // if you hit a letter, increment that amino and go to state/row 3
        // stop codons: TAA, TAG, TGA -> return to state/row 0
        
        {0,0,1,0}, // row 0  // looking for start codon: ATG
        {2,0,1,0},
        {0,0,1,'M'},
        {4,9,14,19}, // row 3  // start to build the codon
        
    //   T | C | A | G
        {5, 6, 7, 8}, // T - -              // row 4
        {'F', 'F', 'L', 'L'}, // T T -      // row 5
        {'S', 'S', 'S', 'S'}, // T C -
        {'Y', 'Y', 0, 0},     // T A -
        {'C', 'C', 0, 'W'},   // T G -      // row 8
        
        {10, 11, 12, 13}, // C - -          // row 9
        {'L', 'L', 'L', 'L'}, // C T -
        {'P', 'P', 'P', 'P'}, // C C -      // row 11
        {'H', 'H', 'Q', 'Q'}, // C A -
        {'R', 'R', 'R', 'R'}, // C G -      // row 13
        
        {15, 16, 17, 18}, // A - -          // row 14
        {'I', 'I', 'I', 'M'}, // A T -
        {'T', 'T', 'T', 'T'}, // A C -      // row 16
        {'N', 'N', 'K', 'K'}, // A A -
        {'S', 'S', 'R', 'R'}, // A G -      // row 18
        
        {20, 21, 22, 23}, // G - -          // row 19
        {'V', 'V', 'V', 'V'}, // G T -
        {'A', 'A', 'A', 'A'}, // G C -      // row 21
        {'D', 'D', 'E', 'E'}, // G A -
        {'G', 'G', 'G', 'G'}  // G G -      // row 23
        
        
        
        
        
    };
    
    
};

#endif /* Translator_hpp */
