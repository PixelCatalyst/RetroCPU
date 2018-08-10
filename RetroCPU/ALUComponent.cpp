#include "Processor.h"

short ALUComponent::SHR(OperandRegs& args)
{
    word count = static_cast<word>(registers[args.sourceReg]);
    if (count > 0)
    {
        word tempBitMask = registers[args.destinationReg] & (1 << (count - 1));
        registers[args.destinationReg] >>= count;
        flags.SetCF(tempBitMask > 0);
        flags.SetZF(registers[args.destinationReg] == 0);
    }
    return 2;
}

short ALUComponent::SHL(OperandRegs& args)
{
    word count = static_cast<word>(registers[args.sourceReg]);
    if (count > 0)
    {
        registers[args.destinationReg] <<= count - 1;
        word tempBitMask = registers[args.destinationReg] & 32768;
        flags.SetCF(tempBitMask > 0);
        registers[args.destinationReg] <<= 1;
        flags.SetZF(registers[args.destinationReg] == 0);
    }
    return 2;
}

short ALUComponent::NOT(byte reg)
{
    registers[reg] = ~registers[reg];
    return 2;
}

short ALUComponent::XOR(OperandRegs& args)
{
    registers[args.destinationReg] ^= registers[args.sourceReg];
    flags.SetZF(registers[args.destinationReg] == 0);
    flags.SetCF(false);
    return 2;
}

short ALUComponent::OR(OperandRegs& args)
{
    registers[args.destinationReg] |= registers[args.sourceReg];
    flags.SetZF(registers[args.destinationReg] == 0);
    flags.SetCF(false);
    return 2;
}

short ALUComponent::AND(OperandRegs& args)
{
    registers[args.destinationReg] &= registers[args.sourceReg];
    flags.SetZF(registers[args.destinationReg] == 0);
    flags.SetCF(false);
    return 2;
}

short ALUComponent::DEC(byte reg)
{
    --registers[reg];
    flags.SetZF(registers[reg] == 0);
    return 2;
}

short ALUComponent::INC(byte reg)
{
    ++registers[reg];
    flags.SetZF(registers[reg] == 0);
    return 2;
}

short ALUComponent::MOD(OperandRegs& args)
{
    if (registers[args.sourceReg] == 0)
        processor.InterruptRequest(0);
    else
    {
        registers[args.destinationReg] %= registers[args.sourceReg];
        flags.SetZF(registers[args.destinationReg] == 0);
    }
    return 2;
}

short ALUComponent::DIV(OperandRegs& args)
{
    if (registers[args.sourceReg] == 0)
        processor.InterruptRequest(0);
    else
        registers[args.destinationReg] /= registers[args.sourceReg];
    return 2;
}

short ALUComponent::MUL(OperandRegs& args)
{
    int source = registers[args.sourceReg];
    int destination = registers[args.destinationReg];
    destination *= source;
    registers[args.destinationReg] = destination;
    flags.SetCF(destination != registers[args.destinationReg]);
    return 2;
}

short ALUComponent::SUB(OperandRegs& args)
{
    registers[args.destinationReg] -= registers[args.sourceReg];
    flags.SetZF(registers[args.destinationReg] == 0);
    flags.SetCF(registers[args.destinationReg] < 0);
    return 2;
}

short ALUComponent::ADD(OperandRegs& args)
{
    registers[args.destinationReg] += registers[args.sourceReg];
    flags.SetZF(registers[args.destinationReg] == 0);
    return 2;
}

short ALUComponent::DispatchBinaryOp(OPCODE opcode)
{
    OperandRegs args = instructionMemory[registers.GetInstructionPointer() + 1];
    switch (opcode)
    {
    case OPCODE::SHR:
        return SHR(args);
    case OPCODE::SHL:
        return SHL(args);
    case OPCODE::XOR:
        return XOR(args);
    case OPCODE::OR:
        return OR(args);
    case OPCODE::AND:
        return AND(args);
    case OPCODE::MOD:
        return MOD(args);
    case OPCODE::DIV:
        return DIV(args);
    case OPCODE::MUL:
        return MUL(args);
    case OPCODE::SUB:
        return SUB(args);
    case OPCODE::ADD:
        return ADD(args);
    default:
        return 1;
    }
}

short ALUComponent::DispatchUnaryOp(OPCODE opcode)
{
    byte reg = instructionMemory[registers.GetInstructionPointer() + 1];
    switch (opcode)
    {
    case OPCODE::NOT:
        return NOT(reg);
    case OPCODE::DEC:
        return DEC(reg);
    case OPCODE::INC:
        return INC(reg);
    }
}

short ALUComponent::Dispatch(OPCODE opcode)
{
    if ((opcode == OPCODE::NOT) || (opcode == OPCODE::DEC) || (opcode == OPCODE::INC))
        return DispatchUnaryOp(opcode);
    else
        return DispatchBinaryOp(opcode);
}

ALUComponent::ALUComponent(Processor& processor) :
    ProcessorComponent(processor)
{}
