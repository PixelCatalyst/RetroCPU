#pragma once

#include "Window.h"
#include "Button.h"
#include "StaticEdit.h"

class CROMSelector : public CWindow
{
private:
	static LRESULT __stdcall Callback(HWND Window, UINT Msg, WPARAM wParam, LPARAM lParam);
	CButton OpenFileButton, RunStopButton;
	CStaticEdit FileNameField;

	void DispatchButtonCommand(HWND ButtonHandle);
public:
	void OnMachineSelfTerminate();

	void Initialize(CVirtualMachine& VM);
	CROMSelector(HINSTANCE Instance);
};