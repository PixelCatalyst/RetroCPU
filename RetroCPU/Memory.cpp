#include "Memory.h"

short Memory::LoadWord(unsigned short address)
{
    short word = cells[address];
    word <<= 8;
    if (address == maxAddress)
        return word;
    return (word += cells[address + 1]);
}

void Memory::StoreWord(unsigned short address, short word)
{
    cells[address] = HIGHBYTE(word);
    if (address < maxAddress)
        cells[address + 1] = LOWBYTE(word);
}

byte& Memory::operator[](unsigned short index)
{
    return cells[index];
}

Memory::Memory()
{
    cells = new byte[sizeInBytes];
    for (unsigned i = 0; i < sizeInBytes; ++i)
        cells[i] = 0;
}

Memory::~Memory()
{
    delete[] cells;
}
