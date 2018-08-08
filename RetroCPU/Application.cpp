#include "Application.h"

void Application::Update()
{
    if (VM.IsRunning())
    {
        bool FollowUpRequest = VM.Cycle();
        if (FollowUpRequest == false)
        {
            VM.Terminate();
        }
    }
}

bool Application::OnInit()
{
    VM.Initialize();
    return true;
}

wxIMPLEMENT_APP(Application);
