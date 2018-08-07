#pragma once

enum class OPCODE : unsigned char 
{
	//Memory instructions
	MOV_REG = 0x01,
	MOV_IMM8 = 0x02,
	MOV_IMM16 = 0x03,
	LDW = 0x04,
	LDB = 0x05,
	STRW = 0x06,
	STRB = 0x07,
	PUSH = 0x08,
	POP = 0x09,
	PUSHF = 0x0A,
	POPF = 0x0B,
	//Arithmetic & logic instructions
	ADD = 0x10,
	SUB = 0x11,
	MUL = 0x12,
	DIV = 0x13,
	MOD = 0x14,
	INC = 0x15,
	DEC = 0x16,
	AND = 0x17,
	OR = 0x18,
	XOR = 0x19,
	NOT = 0x1A,
	SHL = 0x1B,
	SHR = 0x1C,
	//Jump instructions
	JMP_REG = 0x20,
	JMP_IMM16 = 0x21,
	CALL = 0x22,
	RET = 0x23,
	IRET = 0x24,
	CMP = 0x25,
	JZ_JE = 0x26,
	JNZ_JNE = 0x27,
	JA = 0x28,
	JB_JC = 0x29,
	JAE_JNC = 0x2A,
	JBE = 0x2B,
	//Control instructions(I/O + Interrupt)
	OUTB = 0x30,
	OUTW = 0x31,
	INB = 0x32,
	INW = 0x33,
	LIA = 0x34,
	SIM = 0x35,
	CIM = 0x36,
	OFF = 0x37
};

const int CategoriesCount = 4;
enum class OPCODE_CATEGORY : unsigned char
{
	MEMORY = 0,
	ALU = 1,
	JUMP = 2,
	CONTROL = 3
};
