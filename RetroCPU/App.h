#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "VirtualMachine.h"
#include "DirectConsole.h"
#include "ROMSelector.h"

class CApp
{
private:
	CVirtualMachine VM;
	CDirectConsole Console;
	CROMSelector ROMSelector;

	MSG Message;
	bool QuitMessageProcessed = false;
public:
	void Update();
	void HandleMessage();
	bool IfMessagePending();
	bool ShouldNotQuit() const;

	void Initialize();
	CApp(HINSTANCE Instance);
};