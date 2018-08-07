#pragma once

#include "Window.h"

class CStaticEdit : public CWindow
{
private:
public:
	void Initialize(HWND ParentHandle);
	CStaticEdit(HINSTANCE Instance);
};
