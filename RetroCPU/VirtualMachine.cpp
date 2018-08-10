#include "VirtualMachine.h"

using namespace std;

void VirtualMachine::Terminate()
{
    running = false;
}

bool VirtualMachine::Cycle()
{
    return processor.ExecuteInstruction();
}

bool VirtualMachine::IsRunning() const
{
    return running;
}

bool VirtualMachine::LoadROMSegment(ifstream& storage, Memory& targetMemory)
{
    short length = 0;
    storage.read(reinterpret_cast<char*>(&length), 2);
    if (storage.gcount() != 2)
        return false;
    char* buffer = new char[length];
    storage.read(buffer, length);
    if (storage.gcount() != length)
        return false;
    for (int i = 0; i < length; ++i)
        targetMemory[i] = buffer[i];
    delete[] buffer;
    return true;
}

void VirtualMachine::LoadROM(const wstring& path)
{
    if (path.empty() == false)
    {
        ifstream storage(path, ios::binary | ios::beg);
        if (storage.is_open())
        {
            if (LoadROMSegment(storage, dataMemory) == false)
                return;
            if (LoadROMSegment(storage, instructionMemory) == false)
                return;
            running = true;
        }
    }
}

void VirtualMachine::Initialize()
{
    processor.AddDevice(&graphicsCard, 10, 12);
}

VirtualMachine::VirtualMachine() :
    processor(instructionMemory, dataMemory)
{}
