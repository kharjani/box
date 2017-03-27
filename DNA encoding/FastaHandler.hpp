//
//  FastaHandler.hpp
//  dnawx-mac
//
//  Created by Krish on 2/26/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#ifndef FastaHandler_hpp
#define FastaHandler_hpp

#include <iostream>
#include <stdio.h>
#include <fstream>
#include "Exceptions.h"

class FastaHandler
{
public:
    
    FastaHandler(std::string filepath);
    
    ~FastaHandler();
    
    std::string GetSequence();
    
    std::string GetHeader();
    
private:
    
    std::string mHeader;
    std::string mSequence;
    
};

#endif /* FastaHandler_hpp */
