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