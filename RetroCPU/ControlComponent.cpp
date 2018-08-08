#include "Processor.h"

short CControlComponent::InterruptRelatedOp(OPCODE Opcode)
{
    if (Opcode == OPCODE::LIA)
    {
        byte Code = InstructionMemory[Registers.GetInstructionPointer() + 1];
        short Address = InstructionMemory.LoadWord(Registers.GetInstructionPointer() + 2);
        Registers.GetInterruptAddress(Code) = Address;
        return 4;
    }
    else if (Opcode < OPCODE::OFF)
        Flags.SetInterruptMask(Opcode == OPCODE::SIM);
    return 1;
}

short CControlComponent::Dispatch(OPCODE Opcode)
{
    if (Opcode == OPCODE::OFF)
        return -1;
    if (Opcode > OPCODE::INW)
        return InterruptRelatedOp(Opcode);
    byte Port = InstructionMemory[Registers.GetInstructionPointer() + 1];
    byte Reg = InstructionMemory[Registers.GetInstructionPointer() + 2];
    IDevice* pDevice = Processor.GetDevice(Port);
    if (pDevice == nullptr)
        return 3;
    if (Opcode == OPCODE::OUTB)
        pDevice->SendByteTo(Port, Registers[Reg]);
    else if (Opcode == OPCODE::OUTW)
        pDevice->SendWordTo(Port, Registers[Reg]);
    else if (Opcode == OPCODE::INB)
        Registers[Reg] = pDevice->ReceiveByteFrom(Port);
    else if (Opcode == OPCODE::INW)
        Registers[Reg] = pDevice->ReceiveWordFrom(Port);
    return 3;
}

CControlComponent::CControlComponent(CProcessor& Processor) :
    IProcessorComponent(Processor)
{}
