#include "Registers.h"
#include "Memory.h"

void CRegisters::RestoreFromStack(CMemory& DataMemory)
{
    for (int i = RegistersCount - 1; i >= 0; --i)
    {
        Cells[i] = DataMemory.LoadWord(++GetStackPointer());
        ++GetStackPointer();
    }
}

void CRegisters::SaveOnStack(CMemory& DataMemory)
{
    for (int i = 0; i < RegistersCount; ++i)
    {
        DataMemory.StoreWord(--GetStackPointer(), Cells[i]);
        --GetStackPointer();
    }
}

short& CRegisters::GetInterruptAddress(unsigned char Index)
{
    return InterruptAddressTable[Index];
}

short& CRegisters::GetInstructionPointer()
{
    return Cells[GPRegistersCount + 1];
}

short& CRegisters::GetStackPointer()
{
    return Cells[GPRegistersCount];
}

short& CRegisters::operator[](unsigned char Index)
{
    if (Index >= RegistersCount)
        return Cells[0];
    return Cells[Index];
}

CRegisters::CRegisters()
{
    for (int i = 0; i < RegistersCount; ++i)
        Cells[i] = 0;
    for (int i = 0; i < InterruptHandlersCount; ++i)
        InterruptAddressTable[i] = 0;
}
