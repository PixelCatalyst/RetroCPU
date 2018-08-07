#pragma once

#include <vector>

#include "TextRenderer.h"

using std::vector;

class CBrushesManager;
struct DirectConsoleChar;
struct DirectConsoleBufferSize;

struct TextEffect
{
	CharacterFormatSpecifier* pFormat;
	DWRITE_TEXT_RANGE Range;
};

class CDirectWriteTextEffects
{
private:
	vector<TextEffect> Effects;
	CBrushesManager* pBrushesManager;

	void EndEffectsGeneration(DirectConsoleBufferSize* pVisibleBufferSize);
	void AddEffect(DirectConsoleChar& Char, unsigned CharOffset);
public:
	void ApplyToLayout(IDWriteTextLayout* pLayout);
	void Generate(DirectConsoleChar** VisibleBuffer, DirectConsoleBufferSize* pVisibleBufferSize);
	void Clear();

	void Initialize(CBrushesManager* pBrushesManager);
	CDirectWriteTextEffects();
};