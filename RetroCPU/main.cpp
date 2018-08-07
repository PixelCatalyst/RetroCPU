#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
//Windows Common Controls 6.0

#include "App.h"

int __stdcall WinMain(HINSTANCE Instance, HINSTANCE, LPSTR, int)
{
	CApp App(Instance);
	App.Initialize();
	while(App.ShouldNotQuit())
	{
		if(App.IfMessagePending())
			App.HandleMessage();
		else
			App.Update();
	}

	return 0;
}