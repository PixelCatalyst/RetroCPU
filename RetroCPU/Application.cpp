#include <wx/wxprec.h>

#include "Application.h"

void Application::Update()
{
    if (machine.IsRunning())
    {
        bool followUpRequest = machine.Cycle();
        if (followUpRequest == false)
        {
            machine.Terminate();
        }
    }
}

bool Application::OnInit()
{
    machine.Initialize();
    return true;
}

wxIMPLEMENT_APP(Application);
