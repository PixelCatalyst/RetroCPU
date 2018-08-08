#pragma once

#include <string>
#include <fstream>

#include "Processor.h"
#include "Memory.h"

#include "GraphicsCard.h"

using std::wstring;
using std::ifstream;

class CVirtualMachine
{
private:
    CProcessor Processor;
    CMemory InstructionMemory, DataMemory;
    CGraphicsCard GraphicsCard;
    bool Running = false;

    bool LoadROMSegment(ifstream& ROM, CMemory& TargetMemory);
public:
    void Terminate();
    bool Cycle();
    bool IsRunning() const;
    void LoadROM(const wstring& Path);

    void Initialize();
    CVirtualMachine();
};
