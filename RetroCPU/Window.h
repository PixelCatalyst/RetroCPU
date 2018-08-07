#pragma once

#include <windef.h>
#include <WinUser.h>
#include <string>

using std::wstring;

class CWindow
{
protected:
	const wchar_t* ClassName = L"";
	int Style = 0;
	HINSTANCE Instance;
	HWND Handle, ParentHandle;

	void AdjustRect(RECT& Rect, bool VerticalScroll, bool HorizontalScroll);
	void Create(bool SaveThisPointer = true, int ExtendedStyle = 0);
	void Register(WNDPROC WindowCallback, int BackgroundBrush);
public:
	HWND GetHandle();
	wstring GetTitle() const;
	void SetTitle(const wchar_t* Text);
	void SetFont(HFONT FontHandle);
	void SetPosition(int X, int Y);
	void SetSize(int Width, int Height);

	void Repaint();
	void Hide();
	void Show();

	CWindow(HINSTANCE hInstance, HWND ParentHandle, const wchar_t* ClassName);
};