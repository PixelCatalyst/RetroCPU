#include "Registers.h"
#include "Memory.h"

void Registers::RestoreFromStack(Memory& dataMemory)
{
    for (int i = registersCount - 1; i >= 0; --i)
    {
        cells[i] = dataMemory.LoadWord(++GetStackPointer());
        ++GetStackPointer();
    }
}

void Registers::SaveOnStack(Memory& dataMemory)
{
    for (int i = 0; i < registersCount; ++i)
    {
        dataMemory.StoreWord(--GetStackPointer(), cells[i]);
        --GetStackPointer();
    }
}

short& Registers::GetInterruptAddress(unsigned char index)
{
    return interruptAddressTable[index];
}

short& Registers::GetInstructionPointer()
{
    return cells[generalRegistersCount + 1];
}

short& Registers::GetStackPointer()
{
    return cells[generalRegistersCount];
}

short& Registers::operator[](unsigned char index)
{
    if (index >= registersCount)
        return cells[0];
    return cells[index];
}

Registers::Registers()
{
    for (int i = 0; i < registersCount; ++i)
        cells[i] = 0;
    for (int i = 0; i < interruptHandlersCount; ++i)
        interruptAddressTable[i] = 0;
}
