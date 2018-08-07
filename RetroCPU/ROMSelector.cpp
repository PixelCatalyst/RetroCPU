#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "ROMSelector.h"

void CROMSelector::OnMachineSelfTerminate()
{
	RunStopButton.ExecuteCommand();
}

void CROMSelector::DispatchButtonCommand(HWND ButtonHandle)
{
	if(ButtonHandle == OpenFileButton.GetHandle())
		OpenFileButton.ExecuteCommand();
	else if(ButtonHandle == RunStopButton.GetHandle())
		RunStopButton.ExecuteCommand();
}

LRESULT __stdcall CROMSelector::Callback(HWND hWindow, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	CROMSelector* pThis = reinterpret_cast<CROMSelector*>(GetWindowLong(hWindow, 0));
	switch(Msg)
	{
	case WM_COMMAND:
		pThis->DispatchButtonCommand(reinterpret_cast<HWND>(lParam));
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWindow, Msg, wParam, lParam);
	}
}

void CROMSelector::Initialize(CVirtualMachine& VM)
{
	Register(Callback, WHITE_BRUSH);
	Create();
	SetSize(350, 120);
	SetTitle(L"ROM select");

	FileNameField.Initialize(Handle);
	FileNameField.SetPosition(10, 10);
	FileNameField.SetSize(215, 40);
	FileNameField.SetTitle(L"");
	FileNameField.Show();

	OpenFileButton.Initialize(Handle);
	OpenFileButton.SetCommand(new COpenFileCommand(&FileNameField));
	OpenFileButton.SetPosition(230, 10);
	OpenFileButton.SetSize(110, 40);
	OpenFileButton.SetTitle(L"Open ROM file");
	OpenFileButton.Show();

	RunStopButton.Initialize(Handle);
	ICommand* pRunStopCommand = 
		new CCommandSwitch(new CRunMachineCommand(&FileNameField, VM), new CStopMachineCommand(VM), RunStopButton);
	RunStopButton.SetCommand(pRunStopCommand);
	RunStopButton.SetPosition(82, 60);
	RunStopButton.SetSize(165, 50);
	RunStopButton.SetTitle(L"Run");
	RunStopButton.Show();
}

CROMSelector::CROMSelector(HINSTANCE Instance) :
	CWindow(Instance, 0, L"CROMSelector"),
	OpenFileButton(Instance),
	RunStopButton(Instance),
	FileNameField(Instance)
{
	Style = WS_OVERLAPPEDWINDOW & (~WS_THICKFRAME) & (~WS_MAXIMIZEBOX);
}