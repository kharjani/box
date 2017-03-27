//
//  NW.hpp
//  dnawx-mac
//
//  Created by Krish on 3/8/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#ifndef NW_hpp
#define NW_hpp

#include <stdio.h>
#include <iostream>
#include "FastaHandler.hpp"
#include <vector>



class NW
{
    
public:
    
    NW(const std::string& fileA, const std::string& fileB, const std::string& output);
    
    
    
    void Algorithm();
    
    void WriteFile(std::string output);
    
    short GetMax(short a, short b, short c) const;
    
    void GetResult();
    
private:
    
    enum MyEnum : char
    {
        left, above, aboveLeft, none
    };
    
    std::string mSequenceA;
    std::string mSequenceB;
    
    std::vector<std::vector<short>> mScores;
    std::vector<std::vector<MyEnum>> mDirections;
    
    std::string mResultA;
    std::string mResultB;
    
    std::string mHeaderA;
    std::string mHeaderB;
    
    short mFinalScore;
    
    
    
    
    
};



#endif /* NW_hpp */
