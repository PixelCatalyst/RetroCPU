#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "StaticEdit.h"

void CStaticEdit::Initialize(HWND ParentHandle)
{
	this->ParentHandle = ParentHandle;
	Create(false, WS_EX_CLIENTEDGE);
	SetFont(reinterpret_cast<HFONT>(GetStockObject(DEFAULT_GUI_FONT)));
}

CStaticEdit::CStaticEdit(HINSTANCE Instance) :
	CWindow(Instance, 0, L"EDIT")
{
	Style = WS_CHILD | WS_HSCROLL | ES_READONLY | ES_MULTILINE;
}