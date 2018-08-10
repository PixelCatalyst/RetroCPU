#include "Processor.h"

short MemoryComponent::POPF()
{
    flags.RestoreFromStack(registers.GetStackPointer(), dataMemory);
    return 1;
}

short MemoryComponent::PUSHF()
{
    flags.SaveOnStack(registers.GetStackPointer(), dataMemory);
    return 1;
}

short MemoryComponent::POP()
{
    byte reg = instructionMemory[registers.GetInstructionPointer() + 1];
    registers[reg] = dataMemory.LoadWord(++registers.GetStackPointer());
    ++registers.GetStackPointer();
    return 2;
}

short MemoryComponent::PUSH()
{
    byte reg = instructionMemory[registers.GetInstructionPointer() + 1];
    dataMemory.StoreWord(--registers.GetStackPointer(), registers[reg]);
    --registers.GetStackPointer();
    return 2;
}

short MemoryComponent::STRB()
{
    OperandRegs args = instructionMemory[registers.GetInstructionPointer() + 1];
    dataMemory[registers[args.destinationReg]] = registers[args.sourceReg];
    return 2;
}

short MemoryComponent::STRW()
{
    OperandRegs args = instructionMemory[registers.GetInstructionPointer() + 1];
    dataMemory.StoreWord(registers[args.destinationReg], registers[args.sourceReg]);
    return 2;
}

short MemoryComponent::LDB()
{
    OperandRegs args = instructionMemory[registers.GetInstructionPointer() + 1];
    registers[args.destinationReg] = dataMemory[registers[args.sourceReg]];
    return 2;
}

short MemoryComponent::LDW()
{
    OperandRegs args = instructionMemory[registers.GetInstructionPointer() + 1];
    registers[args.destinationReg] = dataMemory.LoadWord(registers[args.sourceReg]);
    return 2;
}

short MemoryComponent::MOV_IMM16()
{
    byte destinationReg = instructionMemory[registers.GetInstructionPointer() + 1];
    short value = instructionMemory.LoadWord(registers.GetInstructionPointer() + 2);
    registers[destinationReg] = value;
    return 4;
}

short MemoryComponent::MOV_IMM8()
{
    byte destinationReg = instructionMemory[registers.GetInstructionPointer() + 1];
    byte value = instructionMemory[registers.GetInstructionPointer() + 2];
    registers[destinationReg] = value;
    return 3;
}

short MemoryComponent::MOV_REG()
{
    OperandRegs args = instructionMemory[registers.GetInstructionPointer() + 1];
    registers[args.destinationReg] = registers[args.sourceReg];
    return 2;
}

short MemoryComponent::Dispatch(OPCODE opcode)
{
    switch (opcode)
    {
    case OPCODE::MOV_REG:
        return MOV_REG();
    case OPCODE::MOV_IMM8:
        return MOV_IMM8();
    case OPCODE::MOV_IMM16:
        return MOV_IMM16();
    case OPCODE::LDW:
        return LDW();
    case OPCODE::LDB:
        return LDB();
    case OPCODE::STRW:
        return STRW();
    case OPCODE::STRB:
        return STRB();
    case OPCODE::PUSH:
        return PUSH();
    case OPCODE::POP:
        return POP();
    case OPCODE::PUSHF:
        return PUSHF();
    case OPCODE::POPF:
        return POPF();
    default:
        return 1;
    }
}

MemoryComponent::MemoryComponent(Processor& processor) :
    ProcessorComponent(processor)
{}
