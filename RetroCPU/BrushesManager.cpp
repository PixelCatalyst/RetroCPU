#include "BrushesManager.h"
#include "ConsoleConstants.h"
#include "SafeRemove.h"

using D2D1::ColorF;
using std::make_pair;

ID2D1SolidColorBrush* CBrushesManager::CreateBrush(int Color)
{
	ID2D1SolidColorBrush* pNewBrush = 0;
	HRESULT Result = pRenderTarget->CreateSolidColorBrush(ColorF(Color), &pNewBrush);
	Brushes.insert(make_pair(Color, pNewBrush));
	return pNewBrush;
}

ID2D1SolidColorBrush* CBrushesManager::GetBrush(int Color)
{
	if(Color == DefaultColor)
		return 0;
	BrushesMap::iterator Iterator = Brushes.find(Color);
	if(Iterator == Brushes.end())
		return CreateBrush(Color);
	else
		return Iterator->second;
}

CBrushesManager::CBrushesManager(ID2D1HwndRenderTarget* pRenderTarget) :
	pRenderTarget(pRenderTarget)
{
	pRenderTarget->AddRef();
}

CBrushesManager::~CBrushesManager()
{
	for(BrushesMap::iterator Iterator = Brushes.begin();Iterator != Brushes.end();++Iterator)
	{
		ID2D1SolidColorBrush* pBrush = Iterator->second;
		SafeRelease(pBrush);
	}
	SafeRelease(pRenderTarget);
}