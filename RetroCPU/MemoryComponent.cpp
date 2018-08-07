#include "Processor.h"

short CMemoryComponent::POPF()
{
	Flags.RestoreFromStack(Registers.GetStackPointer(), DataMemory);
	return 1;
}

short CMemoryComponent::PUSHF()
{
	Flags.SaveOnStack(Registers.GetStackPointer(), DataMemory);
	return 1;
}

short CMemoryComponent::POP()
{
	byte Reg = InstructionMemory[Registers.GetInstructionPointer() + 1];
	Registers[Reg] = DataMemory.LoadWord(++Registers.GetStackPointer());
	++Registers.GetStackPointer();
	return 2;	
}

short CMemoryComponent::PUSH()
{
	byte Reg = InstructionMemory[Registers.GetInstructionPointer() + 1];
	DataMemory.StoreWord(--Registers.GetStackPointer(), Registers[Reg]);
	--Registers.GetStackPointer();
	return 2;	
}

short CMemoryComponent::STRB()
{
	OperandRegs Args = InstructionMemory[Registers.GetInstructionPointer() + 1];
	DataMemory[Registers[Args.DestinationReg]] = Registers[Args.SourceReg];
	return 2;	
}

short CMemoryComponent::STRW()
{
	OperandRegs Args = InstructionMemory[Registers.GetInstructionPointer() + 1];
	DataMemory.StoreWord(Registers[Args.DestinationReg], Registers[Args.SourceReg]);
	return 2;
}

short CMemoryComponent::LDB()
{
	OperandRegs Args = InstructionMemory[Registers.GetInstructionPointer() + 1];
	Registers[Args.DestinationReg] = DataMemory[Registers[Args.SourceReg]]; 
	return 2;
}

short CMemoryComponent::LDW()
{
	OperandRegs Args = InstructionMemory[Registers.GetInstructionPointer() + 1];
	Registers[Args.DestinationReg] = DataMemory.LoadWord(Registers[Args.SourceReg]);
	return 2;
}

short CMemoryComponent::MOV_IMM16()
{
	byte DestinationReg = InstructionMemory[Registers.GetInstructionPointer() + 1];
	short Value = InstructionMemory.LoadWord(Registers.GetInstructionPointer() + 2);
	Registers[DestinationReg] = Value;
	return 4;
}

short CMemoryComponent::MOV_IMM8()
{
	byte DestinationReg = InstructionMemory[Registers.GetInstructionPointer() + 1];
	byte Value = InstructionMemory[Registers.GetInstructionPointer() + 2];
	Registers[DestinationReg] = Value;
	return 3;
}

short CMemoryComponent::MOV_REG()
{
	OperandRegs Args = InstructionMemory[Registers.GetInstructionPointer() + 1];
	Registers[Args.DestinationReg] = Registers[Args.SourceReg]; 
	return 2;
}

short CMemoryComponent::Dispatch(OPCODE Opcode)
{
	switch(Opcode)
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

CMemoryComponent::CMemoryComponent(CProcessor& Processor) :
	IProcessorComponent(Processor)
{}