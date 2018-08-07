#pragma once

#include <map>
#include <queue>

#include "Registers.h"
#include "Flags.h"
#include "Memory.h"
#include "Device.h"
#include "ProcessorComponent.h"

using std::map;
using std::queue;

class CProcessor
{
private:
	CRegisters Registers;
	CFlags Flags;
	CMemory& InstructionMemory;
	CMemory& DataMemory;
	map<word, DeviceRecord> Devices;
	queue<byte> PendingInterruptRequests;

	IProcessorComponent** pComponents = nullptr;

	void HandleInterruptRequest();
public:
	IDevice* GetDevice(word Port);
	void AddDevice(IDevice* pDevice, word MinPort, word MaxPort);

	void InterruptRequest(byte IntCode);
	bool ExecuteInstruction();

	CProcessor(CMemory& InstructionMemory, CMemory& DataMemory);
	~CProcessor();

	friend class IProcessorComponent;
};
