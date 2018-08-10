#pragma once

#include "Opcodes.h"

class Processor;

class ProcessorComponent
{
protected:
    Processor& processor;
    Registers& registers;
    Flags& flags;
    Memory& instructionMemory;
    Memory& dataMemory;
public:
    virtual short Dispatch(OPCODE opcode) = 0;

    ProcessorComponent(Processor& processor);
};

class MemoryComponent : public ProcessorComponent
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

    short Dispatch(OPCODE opcode);

    MemoryComponent(Processor& processor);
};

class ALUComponent : public ProcessorComponent
{
private:
    short DispatchBinaryOp(OPCODE opcode);
    short DispatchUnaryOp(OPCODE opcode);
public:
    short SHR(OperandRegs& args);
    short SHL(OperandRegs& args);
    short NOT(byte reg);
    short XOR(OperandRegs& args);
    short OR(OperandRegs& args);
    short AND(OperandRegs& args);
    short DEC(byte reg);
    short INC(byte reg);
    short MOD(OperandRegs& args);
    short DIV(OperandRegs& args);
    short MUL(OperandRegs& args);
    short SUB(OperandRegs& args);
    short ADD(OperandRegs& args);

    short Dispatch(OPCODE opcode);

    ALUComponent(Processor& processor);
};

class JumpComponent : public ProcessorComponent
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

    short Dispatch(OPCODE opcode);

    JumpComponent(Processor& processor);
};

class ControlComponent : public ProcessorComponent
{
private:
    short InterruptRelatedOp(OPCODE opcode);
public:
    short Dispatch(OPCODE opcode);

    ControlComponent(Processor& processor);
};
