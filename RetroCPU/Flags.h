#pragma once

#include <bitset>

#include "Byte.h"

using std::bitset;

class Memory;

class Flags
{
private:
    bitset<2> flags;
    bitset<2> interruptFlags;
public:
    void RestoreFromStack(short& stackPointer, Memory& dataMemory);
    void SaveOnStack(short& stackPointer, Memory& dataMemory);

    bool GetInterruptMask() const;
    bool GetInterruptInService() const;
    bool GetCF() const;
    bool GetZF() const;
    void SetInterruptMask(bool flag);
    void SetInterruptInService(bool flag);
    void SetCF(bool flag);
    void SetZF(bool flag);
};
