#pragma once

#include "Opcodes.h"

class CProcessor;

class IProcessorComponent
{
protected:
    CProcessor& Processor;
    CRegisters& Registers;
    CFlags& Flags;
    CMemory& InstructionMemory;
    CMemory& DataMemory;
public:
    virtual short Dispatch(OPCODE Opcode) = 0;

    IProcessorComponent(CProcessor& Processor);
};

class CMemoryComponent : public IProcessorComponent
{
public:
    short POPF();
    short PUSHF();
    short POP();
    short PUSH();
    short STRB();
    short STRW();
    short LDB();
    short LDW();
    short MOV_IMM16();
    short MOV_IMM8();
    short MOV_REG();

    short Dispatch(OPCODE Opcode);

    CMemoryComponent(CProcessor& Processor);
};

class CALUComponent : public IProcessorComponent
{
private:
    short DispatchBinaryOp(OPCODE Opcode);
    short DispatchUnaryOp(OPCODE Opcode);
public:
    short SHR(OperandRegs& Args);
    short SHL(OperandRegs& Args);
    short NOT(byte Reg);
    short XOR(OperandRegs& Args);
    short OR(OperandRegs& Args);
    short AND(OperandRegs& Args);
    short DEC(byte Reg);
    short INC(byte Reg);
    short MOD(OperandRegs& Args);
    short DIV(OperandRegs& Args);
    short MUL(OperandRegs& Args);
    short SUB(OperandRegs& Args);
    short ADD(OperandRegs& Args);

    short Dispatch(OPCODE Opcode);

    CALUComponent(CProcessor& Processor);
};

class CJumpComponent : public IProcessorComponent
{
public:
    short JBE();
    short JAE_JNC();
    short JB_JC();
    short JA();
    short JNZ_JNE();
    short JZ_JE();
    short CMP();
    short IRET();
    short RET();
    short CALL();
    short JMP_IMM16();
    short JMP_REG();

    short Dispatch(OPCODE Opcode);

    CJumpComponent(CProcessor& Processor);
};

class CControlComponent : public IProcessorComponent
{
private:
    short InterruptRelatedOp(OPCODE Opcode);
public:
    short Dispatch(OPCODE Opcode);

    CControlComponent(CProcessor& Processor);
};
