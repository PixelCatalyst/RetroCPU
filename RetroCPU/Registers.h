#pragma once

#include "Byte.h"

class Memory;

class Registers
{
private:
    static const int generalRegistersCount = 16;
    static const int specialRegistersCount = 2;
    static const int registersCount = generalRegistersCount + specialRegistersCount;
    static const int interruptHandlersCount = 256;

    short cells[registersCount];
    short interruptAddressTable[interruptHandlersCount];
public:
    void RestoreFromStack(Memory& dataMemory);
    void SaveOnStack(Memory& dataMemory);

    short& GetInterruptAddress(byte index);
    short& GetInstructionPointer();
    short& GetStackPointer();
    short& operator[](byte index);

    Registers();
};
