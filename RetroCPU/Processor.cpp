#include "Processor.h"

IDevice* CProcessor::GetDevice(word Port)
{
	auto DeviceIt = Devices.lower_bound(Port);
	if(DeviceIt == Devices.end())
		return nullptr;
	if((DeviceIt->second.Port > Port) && (DeviceIt->second.IsRightBound == false))
		return nullptr;
	return DeviceIt->second.pDevice;
}

void CProcessor::AddDevice(IDevice* pDevice, word MinPort, word MaxPort)
{
	DeviceRecord NewDevice;
	NewDevice.pDevice = pDevice;
	NewDevice.Port = MinPort;
	Devices[MinPort] = NewDevice;
	if(MinPort == MaxPort)
		return;
	NewDevice.Port = MaxPort;
	NewDevice.IsRightBound = true;
	Devices[MaxPort] = NewDevice;
}

void CProcessor::HandleInterruptRequest()
{
	if((Flags.GetInterruptInService() == false) && (PendingInterruptRequests.empty() == false))
	{
		byte IntCode = PendingInterruptRequests.front();
		PendingInterruptRequests.pop();
		Registers.SaveOnStack(DataMemory);
		Registers.GetInstructionPointer() = Registers.GetInterruptAddress(IntCode);
		Flags.SaveOnStack(Registers.GetStackPointer(), DataMemory);
		Flags.SetInterruptInService(true);
	}
}

void CProcessor::InterruptRequest(byte IntCode)
{
	if(IntCode > 15 && Flags.GetInterruptMask())
		return;
	if(PendingInterruptRequests.size() < 8)
		PendingInterruptRequests.push(IntCode);
}

bool CProcessor::ExecuteInstruction()
{
	byte Opcode = InstructionMemory[Registers.GetInstructionPointer()];
	short InstructionLength = pComponents[HIGHNIBBLE(Opcode)]->Dispatch(static_cast<OPCODE>(Opcode));
	Registers.GetInstructionPointer() += InstructionLength;
	if(InstructionLength < 0)
		return false;
	HandleInterruptRequest();
	return true;
}

CProcessor::CProcessor(CMemory& InstructionMemory, CMemory& DataMemory) :
	InstructionMemory(InstructionMemory),
	DataMemory(DataMemory)
{
	pComponents = new IProcessorComponent*[CategoriesCount];
	pComponents[static_cast<int>(OPCODE_CATEGORY::MEMORY)] = new CMemoryComponent(*this);
	pComponents[static_cast<int>(OPCODE_CATEGORY::ALU)] = new CALUComponent(*this);
	pComponents[static_cast<int>(OPCODE_CATEGORY::JUMP)] = new CJumpComponent(*this);
	pComponents[static_cast<int>(OPCODE_CATEGORY::CONTROL)] = new CControlComponent(*this);
	Registers.GetStackPointer() = CMemory::MaxAddress;
}

CProcessor::~CProcessor()
{
	for(int i = 0;i < CategoriesCount;++i)
		delete pComponents[i];
	delete[] pComponents;
}
