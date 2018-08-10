#include "Processor.h"

short ControlComponent::InterruptRelatedOp(OPCODE opcode)
{
    if (opcode == OPCODE::LIA)
    {
        byte code = instructionMemory[registers.GetInstructionPointer() + 1];
        short address = instructionMemory.LoadWord(registers.GetInstructionPointer() + 2);
        registers.GetInterruptAddress(code) = address;
        return 4;
    }
    else if (opcode < OPCODE::OFF)
        flags.SetInterruptMask(opcode == OPCODE::SIM);
    return 1;
}

short ControlComponent::Dispatch(OPCODE opcode)
{
    if (opcode == OPCODE::OFF)
        return -1;
    if (opcode > OPCODE::INW)
        return InterruptRelatedOp(opcode);
    byte port = instructionMemory[registers.GetInstructionPointer() + 1];
    byte reg = instructionMemory[registers.GetInstructionPointer() + 2];
    Device* device = processor.GetDevice(port);
    if (device == nullptr)
        return 3;
    if (opcode == OPCODE::OUTB)
        device->SendByteTo(port, registers[reg]);
    else if (opcode == OPCODE::OUTW)
        device->SendWordTo(port, registers[reg]);
    else if (opcode == OPCODE::INB)
        registers[reg] = device->ReceiveByteFrom(port);
    else if (opcode == OPCODE::INW)
        registers[reg] = device->ReceiveWordFrom(port);
    return 3;
}

ControlComponent::ControlComponent(Processor& processor) :
    ProcessorComponent(processor)
{}
