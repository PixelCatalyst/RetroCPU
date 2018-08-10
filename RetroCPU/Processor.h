#pragma once

#include <map>
#include <queue>

#include "Registers.h"
#include "Flags.h"
#include "Memory.h"
#include "Device.h"
#include "ProcessorComponent.h"

using std::map;
using std::queue;

class Processor
{
private:
    Registers registers;
    Flags flags;
    Memory& instructionMemory;
    Memory& dataMemory;
    map<word, DeviceRecord> devices;
    queue<byte> pendingInterruptRequests;

    ProcessorComponent** components = nullptr;

    void HandleInterruptRequest();
public:
    Device* GetDevice(word port);
    void AddDevice(Device* device, word minPort, word maxPort);

    void InterruptRequest(byte intCode);
    bool ExecuteInstruction();

    Processor(Memory& instructionMemory, Memory& dataMemory);
    ~Processor();

    friend class ProcessorComponent;
};
