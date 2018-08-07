#pragma once

#include "Byte.h"

class CMemory;

class CRegisters
{
private:
	static const int GPRegistersCount = 16;
	static const int SpecialRegistersCount = 2;
	static const int RegistersCount = GPRegistersCount + SpecialRegistersCount;
	static const int InterruptHandlersCount = 256;

	short Cells[RegistersCount];
	short InterruptAddressTable[InterruptHandlersCount];
public:
	void RestoreFromStack(CMemory& DataMemory);
	void SaveOnStack(CMemory& DataMemory);

	short& GetInterruptAddress(byte Index);
	short& GetInstructionPointer();
	short& GetStackPointer();
	short& operator[](byte Index);
	
	CRegisters();
};
