#include "Flags.h"
#include "Memory.h"

void Flags::RestoreFromStack(short& stackPointer, Memory& dataMemory)
{
    flags = dataMemory[++stackPointer];
}

void Flags::SaveOnStack(short& stackPointer, Memory& dataMemory)
{
    dataMemory[stackPointer--] = flags.to_ulong();
}

bool Flags::GetInterruptMask() const
{
    return interruptFlags[1];
}

bool Flags::GetInterruptInService() const
{
    return interruptFlags[0];
}

bool Flags::GetCF() const
{
    return flags[1];
}

bool Flags::GetZF() const
{
    return flags[0];
}

void Flags::SetInterruptMask(bool flag)
{
    interruptFlags[1] = flag;
}

void Flags::SetInterruptInService(bool flag)
{
    interruptFlags[0] = flag;
}

void Flags::SetCF(bool flag)
{
    flags[1] = flag;
}

void Flags::SetZF(bool flag)
{
    flags[0] = flag;
}
