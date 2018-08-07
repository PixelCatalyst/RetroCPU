#include "DirectWrite.h"
#include "DirectConsoleUtilities.h"
#include "SafeRemove.h"

using namespace D2D1;

void CDirectWrite::Render()
{
	CreateDeviceResources();
	pRenderTarget->BeginDraw();
	pRenderTarget->Clear(BackgroundColor);
	pTextLayout->Draw(0, pTextRenderer, ClientRect.left, ClientRect.top);
	pRenderTarget->EndDraw();
	ValidateRect(Window, &ClientRect);
}

void CDirectWrite::CreateTextLayout(wstring& String)
{
	SafeRelease(pTextLayout);
	HRESULT Result = pDirectWriteFactory->CreateTextLayout(String.c_str(), String.length(), 
		pTextFormat, ClientRect.right, ClientRect.bottom, &pTextLayout);
}

void CDirectWrite::GenerateString(wstring& String,
	DirectConsoleChar** VisibleBuffer, DirectConsoleBufferSize* pVisibleBufferSize)
{
	for(CDirectConsoleCursor BufferCursor(pVisibleBufferSize);BufferCursor.IsLastChangeCorrect();)
	{
		String += BufferCursor.GetChar(VisibleBuffer).Char;
		if(BufferCursor.IsAtEndOfLine())
			String += NewLine;
		BufferCursor.IncrementVisible();
	}
}

void CDirectWrite::FormatText(DirectConsoleChar** VisibleBuffer, DirectConsoleBufferSize* pVisibleBufferSize)
{
	wstring Text;
	GenerateString(Text, VisibleBuffer, pVisibleBufferSize);
	TextEffects.Clear();
	TextEffects.Generate(VisibleBuffer, pVisibleBufferSize);
	CreateTextLayout(Text);
	TextEffects.ApplyToLayout(pTextLayout);
}

void CDirectWrite::ResizeClientArea(int Width, int Height)
{
	ClientRect.left = ClientRect.top = 0;
	ClientRect.right = Width;
	ClientRect.bottom = Height;
	if(pRenderTarget != nullptr)
		HRESULT Result = pRenderTarget->Resize(D2D1_SIZE_U(D2D1::SizeU(Width, Height)));
}

pair<float, float> CDirectWrite::GetCharSize() const
{
	pair<float, float> CharSize = { 0.0f, 0.0f };
	if(pDirectWriteFactory != 0)
	{
		IDWriteTextLayout* pLayoutForMetrics = 0;
		wchar_t TestChar = 219;
		pDirectWriteFactory->CreateTextLayout(&TestChar, 1, pTextFormat, 
			ClientRect.right, ClientRect.bottom, &pLayoutForMetrics);
		DWRITE_TEXT_METRICS TextMetrics;
		pLayoutForMetrics->GetMetrics(&TextMetrics);
		CharSize.first = TextMetrics.width;
		CharSize.second = TextMetrics.height;
	}
	return CharSize;
}

void CDirectWrite::CreateDeviceResources()
{
	if(pRenderTarget == nullptr)
	{
		GetClientRect(Window, &ClientRect);
		D2D_SIZE_U Size = SizeU(ClientRect.right, ClientRect.bottom);
		HRESULT Result = pD2DFactory->CreateHwndRenderTarget(RenderTargetProperties(),
			HwndRenderTargetProperties(Window, Size), &pRenderTarget);
		pRenderTarget->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);
		SafeDelete(pBrushesManager);
		pBrushesManager = new CBrushesManager(pRenderTarget);
		SafeRelease(pTextRenderer);
		pTextRenderer = new CTextRenderer(pRenderTarget);
		pTextRenderer->SetDefaultFontColor(ForegroundColor);
	}
}

void CDirectWrite::CreateDeviceIndependentResources()
{
	HRESULT Result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
	Result = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&pDirectWriteFactory));
	Result = pDirectWriteFactory->CreateTextFormat(FontName, pFontCollection, DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DefaultFontSize, L"en-us", &pTextFormat);
	pTextFormat->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
}

void CDirectWrite::Initialize(HWND Window, int BackgroundColor, int ForegroundColor)
{
	this->Window = Window;
	if(BackgroundColor != DefaultColor)
		this->BackgroundColor = ColorF(BackgroundColor);
	if(ForegroundColor != DefaultColor)
		this->ForegroundColor = ColorF(ForegroundColor);
	CreateDeviceIndependentResources();
	CreateDeviceResources();
	TextEffects.Initialize(pBrushesManager);
}

CDirectWrite::CDirectWrite() :
	pD2DFactory(nullptr),
	pRenderTarget(nullptr),
	pDirectWriteFactory(nullptr),
	pFontCollection(nullptr),
	pTextFormat(nullptr),
	pTextLayout(nullptr),
	pTextRenderer(nullptr),
	pBrushesManager(nullptr),
	BackgroundColor(ColorF(ColorF::Black)),
	ForegroundColor(ColorF(ColorF::LightGray))
{}

void CDirectWrite::Shutdown()
{
	TextEffects.Clear();
	SafeDelete(pBrushesManager);
	SafeRelease(pTextLayout);
	SafeRelease(pTextRenderer);
	SafeRelease(pRenderTarget);
	SafeRelease(pD2DFactory);
	SafeRelease(pTextFormat);
	SafeRelease(pDirectWriteFactory);
}