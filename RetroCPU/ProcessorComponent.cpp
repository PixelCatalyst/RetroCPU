#include "Processor.h"

IProcessorComponent::IProcessorComponent(CProcessor& Processor) :
	Processor(Processor),
	Registers(Processor.Registers),
	Flags(Processor.Flags),
	InstructionMemory(Processor.InstructionMemory),
	DataMemory(Processor.DataMemory)
{}