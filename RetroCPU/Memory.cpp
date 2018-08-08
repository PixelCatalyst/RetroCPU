#include "Memory.h"

short CMemory::LoadWord(unsigned short Address)
{
    short Word = pCells[Address];
    Word <<= 8;
    if (Address == MaxAddress)
        return Word;
    return (Word += pCells[Address + 1]);
}

void CMemory::StoreWord(unsigned short Address, short Word)
{
    pCells[Address] = HIGHBYTE(Word);
    if (Address < MaxAddress)
        pCells[Address + 1] = LOWBYTE(Word);
}

byte& CMemory::operator[](unsigned short Index)
{
    return pCells[Index];
}

CMemory::CMemory()
{
    pCells = new byte[SizeInBytes];
    for (unsigned i = 0; i < SizeInBytes; ++i)
        pCells[i] = 0;
}

CMemory::~CMemory()
{
    delete[] pCells;
}
