#include "RleData.h"
#include <iostream>

void RleData::Compress(const char* input, size_t inSize)
{
	// TODO - compress input data, store in mData (contained in the class)
    
    // use (int) mSize to keep track of the size of mData as you build it
    // so keep adding the next element of compressed data at mData[mSize]
    delete[] mData;
    mSize = 0;
    
    std::cout << "size:  " << inSize << std::endl;
    int i = 0;
    mData = new char[(2*inSize)];
    
    if(inSize == 1)
    {
        char len = 1;
        mData[mSize] = len;
        ++mSize;
        mData[mSize] = input[0];
        return;
    }
    
    while(i < inSize)
    {
        bool posRun = false;
        bool negRun = false;
        int count = 1;
       // std::cout << "INITIAL COUNT: " << count << std::endl;
        char first = input[i];
        int curr = i;
        while(first == input[i+1])
        {
            posRun = true;
            // positive run
            count++;
            i++;
            if(count > 126) break;
            //std::cout << "pos run where i = " << i << std::endl;
        }
        if(posRun)
        {
            
           // std::cout << "mSize is  " << mSize << std::endl;
            char length = static_cast<char>(count);
            
            mData[mSize] = length;
            //std::cout << "just put in mData[mSize]: " << mData[mSize] << " mmm " << count << std::endl;
            
            //++mSize;
            mData[++mSize] = first;
           // std::cout << "a comes out to be  " << mData[mSize] << std::endl;
            ++mSize;
           // std::cout << "end of posRun, count = " << count << " mSize: " << mSize << std::endl;
            posRun = false;
            i++;
            continue;
            
        }
        else{
            // not a positive run, meaning input[i] and input[i+1] are different
            // -> could be a negative run, but also input[i+1] and input[i+2] could be the same, forming a positive run
            if(i >= (inSize - 2)){
                // input[i+1] is the last element
                break;
            }
            //
            if (input[i+1] == input[i+2])
            {
                
                // then input[i] is a single char
                char length = 1;
                mData[mSize] = length;
                mSize++;
                mData[mSize] = input[i];
                continue;  // exit this iteration of the loop, so in the next iteration it'll go into a positive run
            }
            else
            {
                // we have a negative run of length >= 2
                while(input[i] != input[i+1])
                {
                    
                    negRun = true;
                    count++;
                    i++;
                    if(i == (inSize - 1)){
                        // input[i+1] is the last element
                        break;
                    }
                    if(count > 126) break;
                    // only stops looping when it finds 2 identical chars in a row, in which case we need to keep those 2 chars as a pos run
                    
                }
                if(negRun)
                {
                    //count--; // minus 1 cause we included current input[i] even though it's part of a separate positive run that comes next
                    int negCount = count * -1; // negative run, negative value
                    char length = static_cast<char>(negCount);
                    std::cout << "neg count: " << negCount << std::endl;
                    mData[mSize] = length;
                    mSize++;
                    for(int j=curr; j < count+curr; j++)
                    {
                        std:: cout << "input to be added: " << input[j] << std::endl;
                        mData[mSize] = input[j];
                        mSize++;
                    }
                    negRun = false;
                    continue;
                }
            }
            
            
        }
        
    }
    
  //  std::cout << "mhm0: " << mData[0] << " 1:" << mData[1] << " 2: " << mData[2] << " :3 " << mData[3] << " :4 "<< mData[4] << std::endl;
//    for(int k = 0; k < mSize*2; k++){
//       std::cout << mData[k] << " ";
//    }
    
    
    
    
}

void RleData::Decompress(const char* input, size_t inSize, size_t outSize)
{
    // reset
    delete [] mData;
    mSize = 0;
    //setup
    mData = new char[outSize];
    
    int i = 0;
    int count = 0;
    while(i < inSize)
    {
        char curr = input[i];
        count = static_cast<int>(curr);
        i++; // so now input[i] is the char that gets repeated in the positive run
        if(count > 0)
        {
            // positive count, so positive run
            for(int j = 0; j < count; j++) //
            {
                mData[mSize] = input[i];
                std::cout << "will be added to mData: " << input[i] << std::endl;
                mSize++;
            }
        }
        else{
            // assuming it won't ever be 0, we know count is negative, so negative run
            count = count * -1; // convert back to a positive int
            std::cout << "neg count turned pos: " << count << std::endl;
            //i++; // so now input[i] is the first char in the negative run
            for(int j = 0; j < count; j++)
            {
                i++;
                mData[mSize] = input[i];
                mSize++;
               
            }
            
        }
    }
    
    
}

std::ostream& operator<< (std::ostream& stream, const RleData& rhs)
{
	for (int i = 0; i < rhs.mSize; i++)
	{
		stream << rhs.mData[i];
	}
	return stream;
}
