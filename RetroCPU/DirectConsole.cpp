#include "DirectConsole.h"
#include "ConsoleConstants.h"

void CDirectConsole::WriteChar(wchar_t Char, int ForegroundColor, int BackgroundColor)
{
	if(IsNewLineChar(Char))
	{
		Cursor.ToNextLine();
		return;
	}
	if(Char == Tab)
		Char = ' ';
	DirectConsoleChar& ConsoleChar = Cursor.GetChar(Buffer);
	ConsoleChar.Char = Char;
	ConsoleChar.ForegroundColor = ForegroundColor;
	ConsoleChar.BackgroundColor = BackgroundColor;
	Cursor.IncrementTotal();
	TextChanged = true;
	Repaint();
}

void CDirectConsole::SetCursorPosition(COORD& NewPosition)
{
	Cursor.SetPosition(NewPosition);
}

void CDirectConsole::Render()
{
	if(TextChanged)
	{
		unsigned short ScrollPosition = VerticalScroll.GetPosition();
		DirectConsoleChar** VisibleBuffer = &Buffer[ScrollPosition];
		DirectWrite.FormatText(VisibleBuffer, &BufferSize);
		TextChanged = false;
	}
	DirectWrite.Render();
}

LRESULT __stdcall CDirectConsole::Callback(HWND hWindow, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	CDirectConsole* pThis = reinterpret_cast<CDirectConsole*>(GetWindowLong(hWindow, 0));
	switch(Msg)
	{
	case WM_PAINT:
		pThis->Render();
		return 0;
	case WM_CHAR:
		pThis->WriteChar(wParam, 0xFFFF0000, 0xFF00FF11);
		pThis->Repaint();
		return 0;
	case WM_VSCROLL:
		if(pThis->VerticalScroll.OnScrollMessage(wParam))
		{
			pThis->TextChanged = true;
			pThis->Repaint();
		}
		return 0;
	case WM_DESTROY:
		if(pThis->ParentHandle == 0)
			PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWindow, Msg, wParam, lParam);
	}
}

void CDirectConsole::AdjustWindow()
{
	RECT Rect = { 0, 0, 0, 0 };
	pair<float, float> CharSize = DirectWrite.GetCharSize();
	const int RightMargin = 2;
	Rect.right = BufferSize.VisibleColumns * CharSize.first + RightMargin;
	Rect.bottom = BufferSize.VisibleRows * CharSize.second;
	DirectWrite.ResizeClientArea(Rect.right, Rect.bottom);
	CWindow::AdjustRect(Rect, true, false);
}

void CDirectConsole::AllocateBuffer()
{
	int TotalRows = BufferSize.VisibleRows * BufferSize.Pages;
	Buffer = new DirectConsoleChar*[TotalRows];
	for(int i = 0;i < TotalRows;++i)
		Buffer[i] = new DirectConsoleChar[BufferSize.VisibleColumns];
}

void CDirectConsole::Initialize(short Rows, short Columns, short Pages)
{
	BufferSize.VisibleColumns = Columns;
	BufferSize.VisibleRows = Rows;
	BufferSize.Pages = Pages;
	Register(Callback, BLACK_BRUSH);
	Create();
	AllocateBuffer();
	VerticalScroll.Initialize(Handle, Rows, Pages);
	DirectWrite.Initialize(Handle);
	AdjustWindow();
}

CDirectConsole::CDirectConsole(HWND ParentWindow, HINSTANCE Instance) :
	CWindow(Instance, ParentWindow, L"CDirectConsole"),
	TextChanged(true)
{
	Style = WS_OVERLAPPEDWINDOW & (~WS_THICKFRAME);
	Cursor.LinkToBuffer(&BufferSize);
}

void CDirectConsole::Shutdown()
{
	DestroyWindow(Handle);
	DirectWrite.Shutdown();
}