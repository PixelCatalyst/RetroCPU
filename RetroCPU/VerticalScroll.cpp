#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "VerticalScroll.h"

void CVerticalScroll::ProcessScrollingRequest(WPARAM ScrollingRequest, SCROLLINFO* ScrollInfo)
{
	switch(LOWORD(ScrollingRequest))
	{
	case SB_TOP:
		ScrollInfo->nPos = 0;
		break;
	case SB_BOTTOM:
		ScrollInfo->nPos = ScrollInfo->nMax;
		break;
	case SB_LINEUP:
		--ScrollInfo->nPos;
		break;
	case SB_LINEDOWN:
		++ScrollInfo->nPos;
		break;
	case SB_PAGEUP:
		ScrollInfo->nPos -= 2;
		break;
	case SB_PAGEDOWN:
		ScrollInfo->nPos += 2;
		break;
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
		ScrollInfo->nPos = ScrollInfo->nTrackPos;
	}
}

bool CVerticalScroll::OnScrollMessage(WPARAM ScrollingRequest)
{
	if(Visible)
	{
		SCROLLINFO ScrollInfo;
		ScrollInfo.cbSize = sizeof(ScrollInfo);
		ScrollInfo.fMask = SIF_POS | SIF_RANGE | SIF_TRACKPOS;
		GetScrollInfo(Parent, Bar, &ScrollInfo);
		ProcessScrollingRequest(ScrollingRequest, &ScrollInfo);
		ScrollInfo.fMask = SIF_POS;
		SetScrollInfo(Parent, Bar, &ScrollInfo, true);
		return true;
	}
	return false;
}

void inline CVerticalScroll::SetPageSize(unsigned PageSize)
{
	this->PageSize = PageSize;
	SCROLLINFO ScrollInfo;
	ScrollInfo.cbSize = sizeof(ScrollInfo);
	ScrollInfo.fMask = SIF_PAGE;
	ScrollInfo.nPage = PageSize;
	SetScrollInfo(Parent, Bar, &ScrollInfo, true);
}

unsigned CVerticalScroll::GetPageSize() const
{
	return PageSize;
}

unsigned short CVerticalScroll::GetPosition() const
{
	if(Visible == false)
		return 0;
	SCROLLINFO ScrollInfo;
	ScrollInfo.cbSize = sizeof(ScrollInfo);
	ScrollInfo.fMask = SIF_POS;
	GetScrollInfo(Parent, Bar, &ScrollInfo);
	return ScrollInfo.nPos;
}

void CVerticalScroll::UpdateVisibility(unsigned ScrollableElementsCount)
{
	Visible = ScrollableElementsCount >= PageSize;
	if(Visible)
		EnableScrollBar(Parent, Bar, ESB_ENABLE_BOTH);
	else
		EnableScrollBar(Parent, Bar, ESB_DISABLE_BOTH);
}

void CVerticalScroll::SetRange(unsigned MaxRange)
{
	if(Visible)
	{
		SCROLLINFO ScrollInfo;
		ScrollInfo.cbSize = sizeof(ScrollInfo);
		ScrollInfo.nMin = 0;
		ScrollInfo.fMask = SIF_RANGE;
		ScrollInfo.nMax = MaxRange;
		SetScrollInfo(Parent, Bar, &ScrollInfo, true);
	}
}

void CVerticalScroll::Initialize(HWND Parent, unsigned PageSize, unsigned Pages)
{
	this->Parent = Parent;
	this->PageSize = PageSize;
	this->Visible = Pages > 1;
	EnableScrollBar(Parent, Bar, (Visible ? ESB_ENABLE_BOTH : ESB_DISABLE_BOTH));
	SetPageSize(PageSize);
	SetRange((Pages * PageSize) - PageSize);
}

CVerticalScroll::CVerticalScroll() :
	Bar(SB_VERT)
{}