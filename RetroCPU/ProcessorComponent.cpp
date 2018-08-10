#include "Processor.h"

ProcessorComponent::ProcessorComponent(Processor& processor) :
    processor(processor),
    registers(processor.registers),
    flags(processor.flags),
    instructionMemory(processor.instructionMemory),
    dataMemory(processor.dataMemory)
{}
