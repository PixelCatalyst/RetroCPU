#include "Processor.h"

Device* Processor::GetDevice(word port)
{
    auto deviceIt = devices.lower_bound(port);
    if (deviceIt == devices.end())
        return nullptr;
    if ((deviceIt->second.port > port) && (deviceIt->second.isRightBound == false))
        return nullptr;
    return deviceIt->second.device;
}

void Processor::AddDevice(Device* device, word minPort, word maxPort)
{
    DeviceRecord addedDevice;
    addedDevice.device = device;
    addedDevice.port = minPort;
    devices[minPort] = addedDevice;
    if (minPort == maxPort)
        return;
    addedDevice.port = maxPort;
    addedDevice.isRightBound = true;
    devices[maxPort] = addedDevice;
}

void Processor::HandleInterruptRequest()
{
    if ((flags.GetInterruptInService() == false) && (pendingInterruptRequests.empty() == false))
    {
        byte interCode = pendingInterruptRequests.front();
        pendingInterruptRequests.pop();
        registers.SaveOnStack(dataMemory);
        registers.GetInstructionPointer() = registers.GetInterruptAddress(interCode);
        flags.SaveOnStack(registers.GetStackPointer(), dataMemory);
        flags.SetInterruptInService(true);
    }
}

void Processor::InterruptRequest(byte interCode)
{
    if (interCode > 15 && flags.GetInterruptMask())
        return;
    if (pendingInterruptRequests.size() < 8)
        pendingInterruptRequests.push(interCode);
}

bool Processor::ExecuteInstruction()
{
    byte opcode = instructionMemory[registers.GetInstructionPointer()];
    short instructionLength = components[HIGHNIBBLE(opcode)]->Dispatch(static_cast<OPCODE>(opcode));
    registers.GetInstructionPointer() += instructionLength;
    if (instructionLength < 0)
        return false;
    HandleInterruptRequest();
    return true;
}

Processor::Processor(Memory& instructionMemory, Memory& dataMemory) :
    instructionMemory(instructionMemory),
    dataMemory(dataMemory)
{
    components = new ProcessorComponent*[categoriesCount];
    components[static_cast<int>(OPCODE_CATEGORY::MEMORY)] = new MemoryComponent(*this);
    components[static_cast<int>(OPCODE_CATEGORY::ALU)] = new ALUComponent(*this);
    components[static_cast<int>(OPCODE_CATEGORY::JUMP)] = new JumpComponent(*this);
    components[static_cast<int>(OPCODE_CATEGORY::CONTROL)] = new ControlComponent(*this);
    registers.GetStackPointer() = Memory::maxAddress;
}

Processor::~Processor()
{
    for (int i = 0; i < categoriesCount; ++i)
        delete components[i];
    delete[] components;
}
