#pragma once

#include "Byte.h"

class Memory
{
public:
    static const unsigned sizeInBytes = 65536;
    static const unsigned short maxAddress = sizeInBytes - 1;
private:
    byte* cells = nullptr;
public:
    short LoadWord(unsigned short address);
    void StoreWord(unsigned short address, short word);
    byte& operator[](unsigned short index);

    Memory();
    ~Memory();
};
