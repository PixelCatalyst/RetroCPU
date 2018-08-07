#pragma once

#include <dwrite.h>
#include <d2d1.h>

class CharacterFormatSpecifier : public IUnknown
{
private:
	ID2D1SolidColorBrush* pForegroundBrush;
	ID2D1SolidColorBrush* pBackgroundBrush;
	unsigned long RefCount;
public:
	unsigned long __stdcall Release();
	unsigned long __stdcall AddRef();
	HRESULT __stdcall QueryInterface(REFIID riid, void** ppvObject);

	CharacterFormatSpecifier(ID2D1SolidColorBrush* pForegroundBrush, ID2D1SolidColorBrush* pBackgroundBrush = 0) :
		pForegroundBrush(pForegroundBrush),
		pBackgroundBrush(pBackgroundBrush),
		RefCount(1)
	{}
friend class CTextRenderer;
};

class CTextRenderer : public IDWriteTextRenderer
{
private:
	unsigned long RefCount;
	ID2D1HwndRenderTarget* pRenderTarget;
	ID2D1SolidColorBrush* pDefaultForegroundBrush;

	D2D1_RECT_F GetFontRectFromGlyphRun(const DWRITE_GLYPH_RUN* GlyphRun, 
		FLOAT BaselineOriginX, FLOAT BaselineOriginY);
public:
	STDMETHOD(DrawInlineObject)(void*, FLOAT, FLOAT, IDWriteInlineObject*, BOOL, BOOL, IUnknown*);
	STDMETHOD(DrawStrikethrough)(void*, FLOAT, FLOAT, DWRITE_STRIKETHROUGH const*, IUnknown*);
	STDMETHOD(DrawUnderline)(void*, FLOAT, FLOAT, DWRITE_UNDERLINE const*, IUnknown*);

	STDMETHOD(DrawGlyphRun)(
		__maybenull void* ClientDrawingContext,
		FLOAT BaselineOriginX,
		FLOAT BaselineOriginY,
		DWRITE_MEASURING_MODE MeasuringMode,
		__in DWRITE_GLYPH_RUN const* GlyphRun,
		__in DWRITE_GLYPH_RUN_DESCRIPTION const* GlyphRunDescription,
		IUnknown* ClientDrawingEffect
		);

	STDMETHOD(IsPixelSnappingDisabled)(__maybenull void* ClientDrawingContext, __out BOOL* IsDisabled);
	STDMETHOD(GetCurrentTransform)(__maybenull void* ClientDrawingContext, __out DWRITE_MATRIX* Transform);
	STDMETHOD(GetPixelsPerDip)(__maybenull void* ClientDrawingContext, __out FLOAT* PixelsPerDip);

	void SetDefaultFontColor(D2D1_COLOR_F& Color);

	unsigned long __stdcall AddRef();
	HRESULT __stdcall QueryInterface(IID const& rii, void** ppvObject);

	CTextRenderer(ID2D1HwndRenderTarget* pRenderTarget);
	~CTextRenderer();
	unsigned long __stdcall Release();
};