#include "App.h"

void CApp::Update()
{
	if(VM.IsRunning())
	{
		bool FollowUpRequest = VM.Cycle();
		if(FollowUpRequest == false)
		{
			VM.Terminate();
			ROMSelector.OnMachineSelfTerminate();
		}
	}
}

void CApp::HandleMessage()
{
	if(Message.message == WM_QUIT)
		QuitMessageProcessed = true;
	TranslateMessage(&Message);
	DispatchMessage(&Message);
}

bool CApp::IfMessagePending()
{
	if(PeekMessage(&Message, 0, 0, 0, PM_REMOVE))
		return true;
	return false;
}

bool CApp::ShouldNotQuit() const
{
	return !QuitMessageProcessed;
}

void CApp::Initialize()
{
	VM.Initialize();
	Console.Initialize(25, 80, 1);
	Console.SetTitle(L"CPU screen");
	Console.Show();
	ROMSelector.Initialize(VM);
	ROMSelector.Show();
}

CApp::CApp(HINSTANCE Instance) :
	Console(0, Instance),
	ROMSelector(Instance)
{
	Message.message = WM_NULL;
}