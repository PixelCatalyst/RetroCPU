#pragma once

#include "Byte.h"

class CMemory
{
public:
	static const unsigned SizeInBytes = 65536;
	static const unsigned short MaxAddress = SizeInBytes - 1;
private:
	byte* pCells = nullptr;
public:	
	short LoadWord(unsigned short Address);
	void StoreWord(unsigned short Address, short Word);
	byte& operator[](unsigned short Index);
	
	CMemory();
	~CMemory();
};
