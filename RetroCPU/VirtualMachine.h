#pragma once

#include <string>
#include <fstream>

#include "Processor.h"
#include "Memory.h"

#include "GraphicsCard.h"

using std::wstring;
using std::ifstream;

class VirtualMachine
{
private:
    Processor processor;
    Memory instructionMemory, dataMemory;
    GraphicsCard graphicsCard;
    bool running = false;

    bool LoadROMSegment(ifstream& storage, Memory& targetMemory);
public:
    void Terminate();
    bool Cycle();
    bool IsRunning() const;
    void LoadROM(const wstring& path);

    void Initialize();
    VirtualMachine();
};
