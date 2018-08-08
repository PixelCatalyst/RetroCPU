#include "VirtualMachine.h"

using namespace std;

void CVirtualMachine::Terminate()
{
    Running = false;
}

bool CVirtualMachine::Cycle()
{
    return Processor.ExecuteInstruction();
}

bool CVirtualMachine::IsRunning() const
{
    return Running;
}

bool CVirtualMachine::LoadROMSegment(ifstream& ROM, CMemory& TargetMemory)
{
    short Length = 0;
    ROM.read(reinterpret_cast<char*>(&Length), 2);
    if (ROM.gcount() != 2)
        return false;
    char* pBuffer = new char[Length];
    ROM.read(pBuffer, Length);
    if (ROM.gcount() != Length)
        return false;
    for (int i = 0; i < Length; ++i)
        TargetMemory[i] = pBuffer[i];
    delete[] pBuffer;
    return true;
}

void CVirtualMachine::LoadROM(const wstring& Path)
{
    if (Path.empty() == false)
    {
        ifstream ROM(Path, ios::binary | ios::beg);
        if (ROM.is_open())
        {
            if (LoadROMSegment(ROM, DataMemory) == false)
                return;
            if (LoadROMSegment(ROM, InstructionMemory) == false)
                return;
            Running = true;
        }
    }
}

void CVirtualMachine::Initialize()
{
    Processor.AddDevice(&GraphicsCard, 10, 12);
}

CVirtualMachine::CVirtualMachine() :
    Processor(InstructionMemory, DataMemory)
{}
