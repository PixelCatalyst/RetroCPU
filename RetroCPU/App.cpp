#include "App.h"

void CApp::Update()
{
	if(VM.IsRunning())
	{
		bool FollowUpRequest = VM.Cycle();
		if(FollowUpRequest == false)
		{
			VM.Terminate();
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
}

CApp::CApp(HINSTANCE Instance)
{
	Message.message = WM_NULL;
}