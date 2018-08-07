#pragma once

#include <commdlg.h>

#include "Window.h"

class CVirtualMachine;
class CButton;

class ICommand
{
public:
	virtual bool LastUseSuccessful()
	{
		return true;
	}
	virtual void Execute() = 0;
	virtual void SetupOnActivate(CButton& Button)
	{
		return;
	}
};

class COpenFileCommand : public ICommand
{
private:
	OPENFILENAME OpenFN;
	CWindow* pFileNameContainer = nullptr;
public:
	void Execute();

	COpenFileCommand(CWindow* pFileNameContainer);
};

class CStopMachineCommand : public ICommand
{
private:
	CVirtualMachine& VM;
public:
	void Execute();
	void SetupOnActivate(CButton& Button);

	CStopMachineCommand(CVirtualMachine& VM);
};

class CRunMachineCommand : public ICommand
{
private:
	CWindow* pFileNameContainer = nullptr;
	CVirtualMachine& VM;
	bool MachineRan = false;
public:
	bool LastUseSuccessful();
	void Execute();
	void SetupOnActivate(CButton& Button);

	CRunMachineCommand(CWindow* pFileNameContainer, CVirtualMachine& VM);
};

class CCommandSwitch : public ICommand
{
private:
	ICommand* pFirst = nullptr;
	ICommand* pSecond = nullptr;
	CButton& Button;
public:
	void Execute();

	CCommandSwitch(ICommand* pFirst, ICommand* pSecond, CButton& Button);
	~CCommandSwitch();
};

class CButton : public CWindow
{
private:
	ICommand* pCommand = nullptr;
public:
	void ExecuteCommand();
	void SetCommand(ICommand* pCommand);

	void Initialize(HWND ParentHandle);
	CButton(HINSTANCE Instance);
	~CButton();
};