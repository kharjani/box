//
//  NW.cpp
//  dnawx-mac
//
//  Created by Krish on 3/8/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "NW.hpp"

NW::NW(const std::string& fileA, const std::string& fileB, const std::string& output)
{
    // check files are ok
    FastaHandler handlerA(fileA);
    FastaHandler handlerB(fileB);
    mSequenceA = handlerA.GetSequence();
    mSequenceB = handlerB.GetSequence();
    
    mHeaderA = handlerA.GetHeader();
    mHeaderB = handlerB.GetHeader();
    
    
    Algorithm();
    
    GetResult();
    
    WriteFile(output);
    

    
    
}

void NW::Algorithm()
{
    
    //populates the score/direction grid, runs the algorithm, and produces the resultant sequence strings
    
    mScores = std::vector<std::vector<short>>(mSequenceB.size() + 1, std::vector<short>(mSequenceA.size() + 1, 0));
    
    mDirections = std::vector<std::vector<MyEnum>>(mSequenceB.size() + 1, std::vector<MyEnum>(mSequenceA.size() + 1, none));
    
    mDirections[0][0] = none;
    mScores[0][0] = 0;
    
    // fill left-most column and top row
    
    for(int i=1; i < mSequenceA.size() + 1; ++i)
    {
        // top row
        mDirections[0][i] = left;
        mScores[0][i] = (i * -1);
        
    }
    
    for(int i=1; i < mSequenceB.size() +1; ++i)
    {
        // left most column
        mDirections[i][0] = above;
        mScores[i][0] = (i * -1);
    }
    
    // main loop
    
    for(int i=1; i < mSequenceB.size() + 1; ++i)
    {
        for(int j=1; j < mSequenceA.size() + 1; ++j)
        {
            // check above, left, aboveLeft and pick the max
            
            short a; // aboveLeft
            if(mSequenceA[j-1] == mSequenceB[i-1])
            {
                // match
                a = mScores[i-1][j-1] + 1;
                mDirections[i][j] = aboveLeft;
                mScores[i][j] = a;
                continue;
            }
            
            a = mScores[i-1][j-1] - 1;
            short b = mScores[i-1][j] - 1; // above
            short c = mScores[i][j-1] - 1; // left
            
            short max = GetMax(a, b, c);
        
            if(max == a) mDirections[i][j] = aboveLeft;
            else if(max == b) mDirections[i][j] = above;
            else if(max == c) mDirections[i][j] = left;
            
//            if(i == 2 && j == 4)
//            {
//                std::cout << a << " " << b << " " << c << std::endl;
//            }
            
            mScores[i][j] = max;
        }
    }
    
    mFinalScore = mScores[mSequenceB.size()][mSequenceA.size()];
    
    
    
    
}

void NW::GetResult()
{
    short i = mSequenceB.size(); // start at the end
    short j = mSequenceA.size();
    
    while((i != 0) || (j !=0)) // keep going till back at origin
    {
        if(mDirections[i][j] == aboveLeft)
        {
            // write both letters
            mResultA += mSequenceA[j-1];
            mResultB += mSequenceB[i-1];
            i--;
            j--;
        }
        else if(mDirections[i][j] == left)
        {
            mResultA += mSequenceA[j-1];
            mResultB += "_";
            j--;
        }
        else if(mDirections[i][j] == above)
        {
            mResultA += "_";
            mResultB += mSequenceB[i-1];
            i--;
        }
        
    }
    
    
    
    // reverse strings
    std::reverse(mResultA.begin(), mResultA.end());
    std::reverse(mResultB.begin(), mResultB.end());
    
    //std::cout << mResultA << std::endl << mResultB << std::endl;
    
}

short NW::GetMax(short a, short b, short c) const
{
    if(a >= b)
    {
        if(a >= c)
        {
            // above left (priority 1)
            return a;
        }
        else
        {
            return c;
        }
    }
    else
    {
        if(b <= c)
        {
            // left (priority 2)
            return c;
        }
        return b;
    }
}

void NW::WriteFile(std::string output)
{
    std::ofstream outfile(output);
    int charCount = 0; // keep track of chars upto 70 per line
    std::string match;
    std::string subA;
    std::string subB;
    int sectionCount = 0; // to help with the last batch of chars
    if(outfile.is_open())
    {
        outfile << "A: " << mHeaderA << std::endl;
        outfile << "B: " << mHeaderB << std::endl;
        
        outfile << "Score: " << mFinalScore << std::endl << std::endl;
        
        for(int i=0; i < mResultA.size(); ++i)
        {
            if(mResultA[i] == mResultB[i])
            {
                // same amino acid so we need a '|'
                match+= "|";
            }
            else{
                // no match, add a " "
                match+= " ";
            }
            charCount++;
            sectionCount++;
            
            if(sectionCount == 70)
            {   // print data for current batch of 70 characters
                outfile << mResultA.substr(charCount - 70, 70) << std::endl;
                outfile << match << std::endl;
                match = "";
                sectionCount = 0;
                outfile << mResultB.substr(charCount - 70, 70) << std::endl << std::endl;
                                           
            }
            
            
        }
        
        // print last set of characters (probably less than 70)
        subA = mResultA.substr(charCount - sectionCount, sectionCount);
        outfile << subA << std::endl;
        outfile << match << std::endl;
        match = "";
        subB = mResultB.substr(charCount - sectionCount, sectionCount);
        outfile << subB << std::endl << std::endl;
        
        
        outfile.close();
        
        
    }
}
