#pragma once

#include "TextRenderer.h"
#include "BrushesManager.h"
#include "DirectWriteTextEffects.h"
#include "ConsoleConstants.h"

struct DirectConsoleChar;
struct DirectConsoleBufferSize;

using std::wstring;
using std::pair;

class CDirectWrite
{
private:
	const wchar_t* FontName = L"Lucida Console";
	const float DefaultFontSize = 16.0f;

	HWND Window;
	RECT ClientRect;
	ID2D1Factory* pD2DFactory;
	ID2D1HwndRenderTarget* pRenderTarget;
	IDWriteFactory* pDirectWriteFactory;
	IDWriteFontCollection* pFontCollection;
	IDWriteTextFormat* pTextFormat;
	IDWriteTextLayout* pTextLayout;
	CTextRenderer* pTextRenderer;
	CBrushesManager* pBrushesManager;
	CDirectWriteTextEffects TextEffects;

	D2D1_COLOR_F BackgroundColor, ForegroundColor;

	void CreateTextLayout(wstring& String);
	void GenerateString(wstring& String, 
		DirectConsoleChar** VisibleBuffer, DirectConsoleBufferSize* pVisibleBufferSize);
	void CreateDeviceResources();
	void CreateDeviceIndependentResources();
public:
	void Render();
	void FormatText(DirectConsoleChar** VisibleBuffer, DirectConsoleBufferSize* pVisibleBufferSize);
	void ResizeClientArea(int Width, int Height);
	pair<float, float> GetCharSize() const;

	void Initialize(HWND Window, int BackgroundColor = DefaultColor, int ForegroundColor = DefaultColor);
	CDirectWrite();
	void Shutdown();
};