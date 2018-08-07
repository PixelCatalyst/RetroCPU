#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <algorithm>

#include "Button.h"
#include "VirtualMachine.h"
#include "SafeRemove.h"

void CStopMachineCommand::Execute()
{
	VM.Terminate();
}

void CStopMachineCommand::SetupOnActivate(CButton& Button)
{
	Button.SetTitle(L"Stop");
}

CStopMachineCommand::CStopMachineCommand(CVirtualMachine& VM) :
	VM(VM)
{}

bool CRunMachineCommand::LastUseSuccessful()
{
	return MachineRan;
}

void CRunMachineCommand::Execute()
{
	VM.LoadROM(pFileNameContainer->GetTitle());
	MachineRan = VM.IsRunning();
}

void CRunMachineCommand::SetupOnActivate(CButton& Button)
{
	Button.SetTitle(L"Run");
}

CRunMachineCommand::CRunMachineCommand(CWindow* pFileNameContainer, CVirtualMachine& VM) :
	pFileNameContainer(pFileNameContainer),
	VM(VM)
{}

void CCommandSwitch::Execute()
{
	pFirst->Execute();
	if(pFirst->LastUseSuccessful())
	{
		std::swap(pFirst, pSecond);
		pFirst->SetupOnActivate(Button);
	}
}

CCommandSwitch::CCommandSwitch(ICommand* pFirst, ICommand* pSecond, CButton& Button) :
	pFirst(pFirst),
	pSecond(pSecond),
	Button(Button)
{}

CCommandSwitch::~CCommandSwitch()
{
	SafeDelete(pFirst);
	SafeDelete(pSecond);
}

void COpenFileCommand::Execute()
{
	wchar_t FileName[MAX_PATH] = L"";
	OpenFN.lpstrFile = FileName;
	if(GetOpenFileName(&OpenFN))
		pFileNameContainer->SetTitle(FileName);
}

COpenFileCommand::COpenFileCommand(CWindow* pFileNameContainer) :
	pFileNameContainer(pFileNameContainer)
{
	ZeroMemory(&OpenFN, sizeof(OPENFILENAME));
	OpenFN.lStructSize = sizeof(OpenFN);
	OpenFN.lpstrTitle = L"Open ROM file";
	OpenFN.lpstrFilter = L"CPU ROM files(*.rom)\0*.rom\0";
	OpenFN.nMaxFile = MAX_PATH;
	OpenFN.lpstrDefExt = L"rom";
	OpenFN.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
}

void CButton::ExecuteCommand()
{
	if(pCommand != nullptr)
		pCommand->Execute();
}

void CButton::SetCommand(ICommand* pCommand)
{
	SafeDelete(this->pCommand);
	this->pCommand = pCommand;
	pCommand->SetupOnActivate(*this);
}

void CButton::Initialize(HWND ParentHandle)
{
	this->ParentHandle = ParentHandle;
	Create(false);
	SetFont(reinterpret_cast<HFONT>(GetStockObject(DEFAULT_GUI_FONT)));
}

CButton::CButton(HINSTANCE Instance) :
	CWindow(Instance, 0, L"BUTTON")
{
	Style = WS_CHILD;
}

CButton::~CButton()
{
	SafeDelete(pCommand);
}