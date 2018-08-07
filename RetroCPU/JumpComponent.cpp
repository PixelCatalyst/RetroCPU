#include "Processor.h"

short CJumpComponent::JBE()
{
	if(Flags.GetZF() && Flags.GetCF())
		return JMP_IMM16();
	return 3;
}

short CJumpComponent::JAE_JNC()
{
	if(Flags.GetCF() == false)
		return JMP_IMM16();
	return 3;
}

short CJumpComponent::JB_JC()
{
	if(Flags.GetCF())
		return JMP_IMM16();
	return 3;
}

short CJumpComponent::JA()
{
	if((Flags.GetZF() == false) && (Flags.GetCF() == false))
		return JMP_IMM16();
	return 3;
}

short CJumpComponent::JNZ_JNE()
{
	if(Flags.GetZF() == false)
		return JMP_IMM16();
	return 3;
}

short CJumpComponent::JZ_JE()
{
	if(Flags.GetZF())
		return JMP_IMM16();
	return 3;
}

short CJumpComponent::CMP()
{
	OperandRegs Args = InstructionMemory[Registers.GetInstructionPointer() + 1];
	short Compare = Registers[Args.DestinationReg] - Registers[Args.SourceReg];
	Flags.SetZF(Compare == 0);
	Flags.SetCF(Compare < 0);
	return 2;
}

short CJumpComponent::IRET()
{
	Flags.SetInterruptInService(false);
	Flags.RestoreFromStack(Registers.GetStackPointer(), DataMemory);
	Registers.RestoreFromStack(DataMemory);
	return 1;
}

short CJumpComponent::RET()
{
	Registers.GetInstructionPointer() = DataMemory.LoadWord(++Registers.GetStackPointer());
	++Registers.GetStackPointer();
	return 0;
}

short CJumpComponent::CALL()
{
	DataMemory.StoreWord(--Registers.GetStackPointer(), Registers.GetInstructionPointer());
	--Registers.GetStackPointer();
	return JMP_IMM16();
}

short CJumpComponent::JMP_IMM16()
{
	Registers.GetInstructionPointer() = InstructionMemory.LoadWord(Registers.GetInstructionPointer() + 1);
	return 0;
}

short CJumpComponent::JMP_REG()
{
	byte Reg = InstructionMemory[Registers.GetInstructionPointer() + 1];
	Registers.GetInstructionPointer() = Registers[Reg];
	return 0;
}

short CJumpComponent::Dispatch(OPCODE Opcode)
{
	switch(Opcode)
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

CJumpComponent::CJumpComponent(CProcessor& Processor) :
	IProcessorComponent(Processor)
{}