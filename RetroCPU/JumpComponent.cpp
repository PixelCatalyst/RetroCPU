#include "Processor.h"

short JumpComponent::JBE()
{
    if (flags.GetZF() && flags.GetCF())
        return JMP_IMM16();
    return 3;
}

short JumpComponent::JAE_JNC()
{
    if (flags.GetCF() == false)
        return JMP_IMM16();
    return 3;
}

short JumpComponent::JB_JC()
{
    if (flags.GetCF())
        return JMP_IMM16();
    return 3;
}

short JumpComponent::JA()
{
    if ((flags.GetZF() == false) && (flags.GetCF() == false))
        return JMP_IMM16();
    return 3;
}

short JumpComponent::JNZ_JNE()
{
    if (flags.GetZF() == false)
        return JMP_IMM16();
    return 3;
}

short JumpComponent::JZ_JE()
{
    if (flags.GetZF())
        return JMP_IMM16();
    return 3;
}

short JumpComponent::CMP()
{
    OperandRegs args = instructionMemory[registers.GetInstructionPointer() + 1];
    short compare = registers[args.destinationReg] - registers[args.sourceReg];
    flags.SetZF(compare == 0);
    flags.SetCF(compare < 0);
    return 2;
}

short JumpComponent::IRET()
{
    flags.SetInterruptInService(false);
    flags.RestoreFromStack(registers.GetStackPointer(), dataMemory);
    registers.RestoreFromStack(dataMemory);
    return 1;
}

short JumpComponent::RET()
{
    registers.GetInstructionPointer() = dataMemory.LoadWord(++registers.GetStackPointer());
    ++registers.GetStackPointer();
    return 0;
}

short JumpComponent::CALL()
{
    dataMemory.StoreWord(--registers.GetStackPointer(), registers.GetInstructionPointer());
    --registers.GetStackPointer();
    return JMP_IMM16();
}

short JumpComponent::JMP_IMM16()
{
    registers.GetInstructionPointer() = instructionMemory.LoadWord(registers.GetInstructionPointer() + 1);
    return 0;
}

short JumpComponent::JMP_REG()
{
    byte reg = instructionMemory[registers.GetInstructionPointer() + 1];
    registers.GetInstructionPointer() = registers[reg];
    return 0;
}

short JumpComponent::Dispatch(OPCODE opcode)
{
    switch (opcode)
    {
    case OPCODE::JMP_REG:
        return JMP_REG();
    case OPCODE::JMP_IMM16:
        return JMP_IMM16();
    case OPCODE::CALL:
        return CALL();
    case OPCODE::RET:
        return RET();
    case OPCODE::IRET:
        return IRET();
    case OPCODE::CMP:
        return CMP();
    case OPCODE::JZ_JE:
        return JZ_JE();
    case OPCODE::JNZ_JNE:
        return JNZ_JNE();
    case OPCODE::JA:
        return JA();
    case OPCODE::JB_JC:
        return JB_JC();
    case OPCODE::JAE_JNC:
        return JAE_JNC();
    case OPCODE::JBE:
        return JBE();
    default:
        return 1;
    }
}

JumpComponent::JumpComponent(Processor& processor) :
    ProcessorComponent(processor)
{}
