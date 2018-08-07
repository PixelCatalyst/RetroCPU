#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "Window.h"

HWND CWindow::GetHandle()
{
	return Handle;
}

wstring CWindow::GetTitle() const
{
	wchar_t Buffer[MAX_PATH];
	GetWindowText(Handle, Buffer, MAX_PATH);
	return wstring(Buffer);
}

void CWindow::SetTitle(const wchar_t* Text)
{
	SetWindowTextW(Handle, Text);
}

void CWindow::SetFont(HFONT FontHandle)
{
	SendMessage(Handle, WM_SETFONT, reinterpret_cast<WPARAM>(FontHandle), 0);
}

void CWindow::SetPosition(int X, int Y)
{
	SetWindowPos(Handle, 0, X, Y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void CWindow::AdjustRect(RECT& Rect, bool VerticalScroll, bool HorizontalScroll)
{
	AdjustWindowRect(&Rect, Style, false);
	int Width = Rect.right - Rect.left + (VerticalScroll ? GetSystemMetrics(SM_CXVSCROLL) : 0);
	int Height = Rect.bottom - Rect.top + (HorizontalScroll ? GetSystemMetrics(SM_CYHSCROLL) : 0);
	SetWindowPos(Handle, 0, 0, 0, Width, Height, SWP_NOMOVE | SWP_NOZORDER);
}

void CWindow::SetSize(int Width, int Height)
{
	RECT Rect;
	Rect.left = Rect.top = 0;
	Rect.right = Width;
	Rect.bottom = Height;
	AdjustRect(Rect, false, false);
}

void CWindow::Repaint()
{
	RECT Rect;
	GetClientRect(Handle, &Rect);
	InvalidateRect(Handle, &Rect, false);
}

void CWindow::Hide()
{
	ShowWindow(Handle, SW_HIDE);
}

void CWindow::Show()
{
	ShowWindow(Handle, SW_SHOW);
}

void CWindow::Create(bool SaveThisPointer, int ExtendedStyle)
{
	Handle = CreateWindowEx(ExtendedStyle, ClassName, ClassName, Style, 
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, ParentHandle, 0, Instance, 0);
	if(SaveThisPointer)
		SetWindowLong(Handle, 0, reinterpret_cast<LONG>(this));
}

void CWindow::Register(WNDPROC WindowCallback, int BackgroundBrush)
{
	WNDCLASSEX WndClass;
	ZeroMemory(&WndClass, sizeof(WndClass));
	WndClass.cbSize = sizeof(WndClass);
	WndClass.cbWndExtra = sizeof(CWindow*);
	WndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(BackgroundBrush));
	WndClass.hCursor = LoadCursor(0, IDC_ARROW);
	WndClass.hIcon = LoadIcon(0, IDI_APPLICATION);
	WndClass.hInstance = Instance;
	WndClass.lpszClassName = ClassName;
	WndClass.lpfnWndProc = WindowCallback;
	RegisterClassEx(&WndClass);
}

CWindow::CWindow(HINSTANCE Instance, HWND ParentHandle, const wchar_t* ClassName) :
	Handle(0),
	Instance(Instance),
	ParentHandle(ParentHandle),
	ClassName(ClassName)
{}