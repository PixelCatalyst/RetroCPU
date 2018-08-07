#pragma once

#include <d2d1.h>
#include <map>

using std::map;

class CBrushesManager
{
private:
	ID2D1HwndRenderTarget* pRenderTarget;

	using BrushesMap = map<int, ID2D1SolidColorBrush*>;
	BrushesMap Brushes;

	ID2D1SolidColorBrush* CreateBrush(int Color);
public:
	ID2D1SolidColorBrush* GetBrush(int Color);

	CBrushesManager(ID2D1HwndRenderTarget* pRenderTarget);
	~CBrushesManager();
};