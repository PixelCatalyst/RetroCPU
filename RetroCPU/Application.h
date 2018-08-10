#pragma once

#include <wx/app.h>

#include "VirtualMachine.h"

class Application : public wxApp
{
private:
    VirtualMachine machine;
public:
    void Update();

    bool OnInit() override;
};
