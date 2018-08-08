#pragma once

#include <wx/app.h>

#include "VirtualMachine.h"

class Application : public wxApp
{
private:
    CVirtualMachine VM;
public:
    void Update();

    bool OnInit() override;
};
