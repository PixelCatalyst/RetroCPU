#pragma once

#include <bitset>

#include "Byte.h"

using std::bitset;

class CMemory;

class CFlags
{
private:
	bitset<2> Flags;
	bitset<2> InterruptFlags;
public:
	void RestoreFromStack(short& StackPointer, CMemory& DataMemory);
	void SaveOnStack(short& StackPointer, CMemory& DataMemory);

	bool GetInterruptMask() const;
	bool GetInterruptInService() const;
	bool GetCF() const;
	bool GetZF() const;
	void SetInterruptMask(bool Flag);
	void SetInterruptInService(bool Flag);
	void SetCF(bool Flag);
	void SetZF(bool Flag);
};