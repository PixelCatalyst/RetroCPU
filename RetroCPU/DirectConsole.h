#pragma once

#include <string>

#include "ConsoleConstants.h"
#include "DirectWrite.h"
#include "VerticalScroll.h"
#include "DirectConsoleUtilities.h"
#include "Window.h"

using std::wstring;

class CDirectConsole : public CWindow
{
private:
	DirectConsoleBufferSize BufferSize;
	DirectConsoleChar** Buffer;
	CDirectConsoleCursor Cursor;
	CDirectWrite DirectWrite;
	CVerticalScroll VerticalScroll;
	bool TextChanged;

	void Render();
	static LRESULT __stdcall Callback(HWND Window, UINT Msg, WPARAM wParam, LPARAM lParam);

	void AdjustWindow();
	void AllocateBuffer();
public:
	void WriteChar(wchar_t Char, int ForegroundColor = DefaultColor, int BackgroundColor = DefaultColor);
	void SetCursorPosition(COORD& NewPosition);

	void SetSize(int, int) = delete;

	void Initialize(short Rows, short Columns, short Pages);
	CDirectConsole(HWND ParentWindow, HINSTANCE Instance);
	void Shutdown();
};