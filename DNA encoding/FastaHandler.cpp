//
//  FastaHandler.cpp
//  dnawx-mac
//
//  Created by Krish on 2/26/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "FastaHandler.hpp"

FastaHandler::FastaHandler(std::string filepath)
{
    
    std::ifstream::pos_type size;
    std::ifstream inputFile(filepath, std::ios::in|std::ios::ate);
    size = inputFile.tellg();
    mSequence.reserve(size);
    inputFile.seekg (0, std::ios::beg);
    if(inputFile.is_open())
    {
        getline(inputFile, mHeader);
       
        
       
        if(mHeader[0] == '>')
        {
            mHeader = mHeader.erase(0,1);
            char c;
            while(inputFile.get(c))
            {
                if(c== 'T' || c == 'C' || c == 'A' || c == 'G')
                {
                    mSequence += c;
                    
                }
                else if (c == '\n' || c == '\r' || c == '\xff')
                {
                    // skip char
                    continue;
                }
                else
                {
                    // throw invalid file contents
                    throw FileReadExcept();
                }
            }
   
            
            
        }
        else{
            // throw exception for invalid file contents
            throw FileReadExcept();
            
        }
        
        
    }
    else
    {
        // throw some sort of file error exception?
        
        throw FileLoadExcept();
    }
}

FastaHandler::~FastaHandler()
{
    
}

std::string FastaHandler::GetSequence()
{
    return mSequence;
}

std::string FastaHandler::GetHeader()
{
    return mHeader;
}
