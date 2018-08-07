#include "Processor.h"

short CALUComponent::SHR(OperandRegs& Args)
{
	word Count = static_cast<word>(Registers[Args.SourceReg]);
	if(Count > 0)
	{
		word TempBitMask = Registers[Args.DestinationReg] & (1 << (Count - 1));
		Registers[Args.DestinationReg] >>= Count;
		Flags.SetCF(TempBitMask > 0);
		Flags.SetZF(Registers[Args.DestinationReg] == 0);
	}
	return 2;
}

short CALUComponent::SHL(OperandRegs& Args)
{
	word Count = static_cast<word>(Registers[Args.SourceReg]);
	if(Count > 0)
	{
		Registers[Args.DestinationReg] <<= Count - 1;
		word TempBitMask = Registers[Args.DestinationReg] & 32768;
		Flags.SetCF(TempBitMask > 0);
		Registers[Args.DestinationReg] <<= 1;
		Flags.SetZF(Registers[Args.DestinationReg] == 0);	
	}
	return 2;
}

short CALUComponent::NOT(byte Reg)
{
	Registers[Reg] = ~Registers[Reg];
	return 2;
}

short CALUComponent::XOR(OperandRegs& Args)
{
	Registers[Args.DestinationReg] ^= Registers[Args.SourceReg];
	Flags.SetZF(Registers[Args.DestinationReg] == 0);
	Flags.SetCF(false);
	return 2;
}

short CALUComponent::OR(OperandRegs& Args)
{
	Registers[Args.DestinationReg] |= Registers[Args.SourceReg];
	Flags.SetZF(Registers[Args.DestinationReg] == 0);
	Flags.SetCF(false);
	return 2;
}

short CALUComponent::AND(OperandRegs& Args)
{
	Registers[Args.DestinationReg] &= Registers[Args.SourceReg];
	Flags.SetZF(Registers[Args.DestinationReg] == 0);
	Flags.SetCF(false);
	return 2;
}

short CALUComponent::DEC(byte Reg)
{
	--Registers[Reg];
	Flags.SetZF(Registers[Reg] == 0);
	return 2;
}

short CALUComponent::INC(byte Reg)
{
	++Registers[Reg];
	Flags.SetZF(Registers[Reg] == 0);
	return 2;
}

short CALUComponent::MOD(OperandRegs& Args)
{
	if(Registers[Args.SourceReg] == 0)
		Processor.InterruptRequest(0);
	else
	{
		Registers[Args.DestinationReg] %= Registers[Args.SourceReg];
		Flags.SetZF(Registers[Args.DestinationReg] == 0);
	}
	return 2;
}

short CALUComponent::DIV(OperandRegs& Args)
{
	if(Registers[Args.SourceReg] == 0)
		Processor.InterruptRequest(0);
	else
		Registers[Args.DestinationReg] /= Registers[Args.SourceReg];
	return 2;
}

short CALUComponent::MUL(OperandRegs& Args)
{
	int Source = Registers[Args.SourceReg];
	int Destination = Registers[Args.DestinationReg];
	Destination *= Source;
	Registers[Args.DestinationReg] = Destination;
	Flags.SetCF(Destination != Registers[Args.DestinationReg]);
	return 2;
}

short CALUComponent::SUB(OperandRegs& Args)
{
	Registers[Args.DestinationReg] -= Registers[Args.SourceReg];
	Flags.SetZF(Registers[Args.DestinationReg] == 0);
	Flags.SetCF(Registers[Args.DestinationReg] < 0);
	return 2;
}

short CALUComponent::ADD(OperandRegs& Args)
{
	Registers[Args.DestinationReg] += Registers[Args.SourceReg];
	Flags.SetZF(Registers[Args.DestinationReg] == 0);
	return 2;
}

short CALUComponent::DispatchBinaryOp(OPCODE Opcode)
{
	OperandRegs Args = InstructionMemory[Registers.GetInstructionPointer() + 1];
	switch(Opcode)
	{
	case OPCODE::SHR:
		return SHR(Args);
	case OPCODE::SHL:
		return SHL(Args);
	case OPCODE::XOR:
		return XOR(Args);
	case OPCODE::OR:
		return OR(Args);
	case OPCODE::AND:
		return AND(Args);
	case OPCODE::MOD:
		return MOD(Args);
	case OPCODE::DIV:
		return DIV(Args);
	case OPCODE::MUL:
		return MUL(Args);
	case OPCODE::SUB:
		return SUB(Args);
	case OPCODE::ADD:
		return ADD(Args);
	default:
		return 1;
	}
}

short CALUComponent::DispatchUnaryOp(OPCODE Opcode)
{
	byte Reg = InstructionMemory[Registers.GetInstructionPointer() + 1];
	switch(Opcode)
	{
	case OPCODE::NOT:
		return NOT(Reg);
	case OPCODE::DEC:
		return DEC(Reg);
	case OPCODE::INC:
		return INC(Reg);
	}
}

short CALUComponent::Dispatch(OPCODE Opcode)
{
	if((Opcode == OPCODE::NOT) || (Opcode == OPCODE::DEC) || (Opcode == OPCODE::INC))
		return DispatchUnaryOp(Opcode);
	else
		return DispatchBinaryOp(Opcode);
}

CALUComponent::CALUComponent(CProcessor& Processor) :
	IProcessorComponent(Processor)
{}
