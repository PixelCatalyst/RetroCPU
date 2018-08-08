#pragma once

using byte = unsigned char;
using word = unsigned short;

#define LOWNIBBLE(x) (x & 0x0F)
#define HIGHNIBBLE(x) (x >> 4)

#define LOWBYTE(x) (x & 0x00FF)
#define HIGHBYTE(x) (x >> 8)

struct OperandRegs
{
public:
    byte DestinationReg;
    byte SourceReg;

    OperandRegs(byte Args) :
        DestinationReg(HIGHNIBBLE(Args)),
        SourceReg(LOWNIBBLE(Args))
    {}
};
