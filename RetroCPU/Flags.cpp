#include "Flags.h"
#include "Memory.h"

void CFlags::RestoreFromStack(short& StackPointer, CMemory& DataMemory)
{
	Flags = DataMemory[++StackPointer];
}

void CFlags::SaveOnStack(short& StackPointer, CMemory& DataMemory)
{
	DataMemory[StackPointer--] = Flags.to_ulong();
}

bool CFlags::GetInterruptMask() const
{
	return InterruptFlags[1];
}

bool CFlags::GetInterruptInService() const
{
	return InterruptFlags[0];
}

bool CFlags::GetCF() const
{
	return Flags[1];
}

bool CFlags::GetZF() const
{
	return Flags[0];
}

void CFlags::SetInterruptMask(bool Flag)
{
	InterruptFlags[1] = Flag;
}

void CFlags::SetInterruptInService(bool Flag)
{
	InterruptFlags[0] = Flag;
}

void CFlags::SetCF(bool Flag)
{
	Flags[1] = Flag;
}

void CFlags::SetZF(bool Flag)
{
	Flags[0] = Flag;
}