#include "DirectWriteTextEffects.h"
#include "DirectConsoleUtilities.h"
#include "BrushesManager.h"
#include "ConsoleConstants.h"
#include "SafeRemove.h"

void CDirectWriteTextEffects::ApplyToLayout(IDWriteTextLayout* pLayout)
{
	for(unsigned i = 0;i < Effects.size();++i)
	{
		TextEffect CurrentEffect = Effects[i];
		pLayout->SetDrawingEffect(CurrentEffect.pFormat, CurrentEffect.Range);
	}
}

void CDirectWriteTextEffects::EndEffectsGeneration(DirectConsoleBufferSize* pVisibleBufferSize)
{
	if(Effects.empty())
		return;
	DWRITE_TEXT_RANGE& LastEffectRange = Effects.back().Range;
	if(LastEffectRange.length == 0)
	{
		unsigned TotalNumberOfChars = (pVisibleBufferSize->VisibleRows * pVisibleBufferSize->VisibleColumns)
			+ pVisibleBufferSize->VisibleColumns - 1;
		LastEffectRange.length = TotalNumberOfChars - LastEffectRange.startPosition;
	}
}

void CDirectWriteTextEffects::AddEffect(DirectConsoleChar& Char, unsigned CharOffset)
{
	if(Effects.empty() == false)
	{
		DWRITE_TEXT_RANGE& PreviousRange = Effects.back().Range;
		if(PreviousRange.length == 0)
			PreviousRange.length = CharOffset - PreviousRange.startPosition;
	}
	if((Char.ForegroundColor == DefaultColor) && (Char.BackgroundColor == DefaultColor))
		return;
	TextEffect NewEffect;
	ID2D1SolidColorBrush* pForegoundBrush = pBrushesManager->GetBrush(Char.ForegroundColor);
	ID2D1SolidColorBrush* pBackgoundBrush = pBrushesManager->GetBrush(Char.BackgroundColor);
	NewEffect.pFormat = new CharacterFormatSpecifier(pForegoundBrush, pBackgoundBrush);
	NewEffect.Range.startPosition = CharOffset;
	NewEffect.Range.length = 0;
	Effects.push_back(NewEffect);
}

void CDirectWriteTextEffects::Generate(DirectConsoleChar** VisibleBuffer, DirectConsoleBufferSize* pVisibleBufferSize)
{
	int CurrentForegroundColor = DefaultColor;
	int CurrentBackgroundColor = DefaultColor;
	for(CDirectConsoleCursor BufferCursor(pVisibleBufferSize);BufferCursor.IsLastChangeCorrect();)
	{
		DirectConsoleChar& Char = BufferCursor.GetChar(VisibleBuffer);
		if((Char.BackgroundColor != CurrentBackgroundColor) || (Char.ForegroundColor != CurrentForegroundColor))
		{
			AddEffect(Char, BufferCursor.GetOffset() + BufferCursor.GetY());
			CurrentForegroundColor = Char.ForegroundColor;
			CurrentBackgroundColor = Char.BackgroundColor;
		}
		BufferCursor.IncrementVisible();
	}
	EndEffectsGeneration(pVisibleBufferSize);
}

void CDirectWriteTextEffects::Clear()
{
	for(unsigned i = 0;i < Effects.size();++i)
		SafeRelease(Effects[i].pFormat);
	Effects.clear();
}

void CDirectWriteTextEffects::Initialize(CBrushesManager* pBrushesManager)
{
	Effects.clear();
	this->pBrushesManager = pBrushesManager;
}

CDirectWriteTextEffects::CDirectWriteTextEffects() :
	pBrushesManager(0)
{}