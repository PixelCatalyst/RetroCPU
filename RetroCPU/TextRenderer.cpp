#include "TextRenderer.h"
#include "ConsoleConstants.h"
#include "SafeRemove.h"

using namespace D2D1;

unsigned long __stdcall CharacterFormatSpecifier::Release()
{
	unsigned long NewCount = InterlockedDecrement(&RefCount);
	if(NewCount == 0)
		delete this;
	return NewCount;
}

unsigned long __stdcall CharacterFormatSpecifier::AddRef()
{
	return InterlockedIncrement(&RefCount);
}

HRESULT __stdcall CharacterFormatSpecifier::QueryInterface(REFIID riid, void** ppvObject)
{
	if(riid == __uuidof(IUnknown))
		*ppvObject = this;
	else
	{
		*ppvObject = 0;
		return E_FAIL;
	}
	AddRef();
	return S_OK;
}

STDMETHODIMP CTextRenderer::DrawInlineObject(void*, FLOAT, FLOAT, IDWriteInlineObject*, BOOL, BOOL, IUnknown*)
{
	return E_NOTIMPL;
}

STDMETHODIMP CTextRenderer::DrawStrikethrough(void*, FLOAT, FLOAT, DWRITE_STRIKETHROUGH const*, IUnknown*)
{
	return E_NOTIMPL;
}

STDMETHODIMP CTextRenderer::DrawUnderline(void*, FLOAT, FLOAT, DWRITE_UNDERLINE const*, IUnknown*)
{
	return E_NOTIMPL;
}

D2D1_RECT_F CTextRenderer::GetFontRectFromGlyphRun(const DWRITE_GLYPH_RUN* GlyphRun,
	FLOAT BaselineOriginX, FLOAT BaselineOriginY)
{
	float TotalWidth = 0;
	for(unsigned i = 0;i < GlyphRun->glyphCount;++i)
		TotalWidth += GlyphRun->glyphAdvances[i];

	DWRITE_FONT_METRICS FontMetrics;
	GlyphRun->fontFace->GetMetrics(&FontMetrics);
	float Adjust = GlyphRun->fontEmSize / FontMetrics.designUnitsPerEm;
	float Ascent = Adjust * FontMetrics.ascent + 0.5;
	float Descent = Adjust * FontMetrics.descent;
	D2D1_RECT_F FontRect = RectF(BaselineOriginX, BaselineOriginY - Ascent,
		BaselineOriginX + TotalWidth, BaselineOriginY + Descent);
	return FontRect;
}

STDMETHODIMP CTextRenderer::DrawGlyphRun(
	__maybenull void* ClientDrawingContext,
	FLOAT BaselineOriginX,
	FLOAT BaselineOriginY,
	DWRITE_MEASURING_MODE MeasuringMode,
	__in DWRITE_GLYPH_RUN const* GlyphRun,
	__in DWRITE_GLYPH_RUN_DESCRIPTION const* GlyphRunDescription,
	IUnknown* ClientDrawingEffect
	)
{
	ID2D1Brush* pForegroundBrush = pDefaultForegroundBrush;
	CharacterFormatSpecifier* pFormatSpecifier = static_cast<CharacterFormatSpecifier*>(ClientDrawingEffect);
	if(pFormatSpecifier != 0)
	{
		if(pFormatSpecifier->pForegroundBrush != 0)
			pForegroundBrush = pFormatSpecifier->pForegroundBrush;
		if(pFormatSpecifier->pBackgroundBrush != 0)
		{
			D2D1_RECT_F FontRect = GetFontRectFromGlyphRun(GlyphRun, BaselineOriginX, BaselineOriginY);
			pRenderTarget->FillRectangle(FontRect, pFormatSpecifier->pBackgroundBrush);
		}
	}
	pRenderTarget->DrawGlyphRun(Point2F(BaselineOriginX, BaselineOriginY), GlyphRun, pForegroundBrush, MeasuringMode);
	return S_OK;
}

STDMETHODIMP CTextRenderer::IsPixelSnappingDisabled(__maybenull void* ClientDrawingContext, __out BOOL* IsDisabled)
{
	*IsDisabled = FALSE;
	return S_OK;
}

STDMETHODIMP CTextRenderer::GetCurrentTransform(__maybenull void* ClientDrawingContext, __out DWRITE_MATRIX* Transform)
{
	pRenderTarget->GetTransform(reinterpret_cast<D2D1_MATRIX_3X2_F*>(Transform));
	return S_OK;
}

STDMETHODIMP CTextRenderer::GetPixelsPerDip(__maybenull void* ClientDrawingContext, __out FLOAT* PixelsPerDip)
{
	float XDPI, YDPI;
	pRenderTarget->GetDpi(&XDPI, &YDPI);
	*PixelsPerDip = XDPI / DefaultDPI;
	return S_OK;
}

void CTextRenderer::SetDefaultFontColor(D2D1_COLOR_F& Color)
{
	SafeRelease(pDefaultForegroundBrush);
	HRESULT Result = pRenderTarget->CreateSolidColorBrush(Color, &pDefaultForegroundBrush);
}

unsigned long __stdcall CTextRenderer::AddRef()
{
	return InterlockedIncrement(&RefCount);
}

HRESULT __stdcall CTextRenderer::QueryInterface(IID const& riid, void** ppvObject)
{
	if(__uuidof(IDWriteTextRenderer) == riid)
		*ppvObject = this;
	else if(__uuidof(IDWritePixelSnapping) == riid)
		*ppvObject = this;
	else if(__uuidof(IUnknown) == riid)
		*ppvObject = this;
	else
	{
		*ppvObject = NULL;
		return E_FAIL;
	}
	AddRef();
	return S_OK;
}


CTextRenderer::CTextRenderer(ID2D1HwndRenderTarget* pRenderTarget) :
	pRenderTarget(pRenderTarget),
	RefCount(1)
{
	pRenderTarget->AddRef();
}

CTextRenderer::~CTextRenderer()
{
	SafeRelease(pDefaultForegroundBrush);
	SafeRelease(pRenderTarget);
}

unsigned long __stdcall CTextRenderer::Release()
{
	unsigned long NewCount = InterlockedDecrement(&RefCount);
	if(NewCount == 0)
		delete this;
	return NewCount;
}