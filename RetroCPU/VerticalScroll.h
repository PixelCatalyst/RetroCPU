#pragma once

#include <windef.h>

class CVerticalScroll
{
protected:
	HWND Parent;
	int Bar;
	unsigned PageSize;
	bool Visible;

	void virtual ProcessScrollingRequest(WPARAM ScrollingRequest, SCROLLINFO* ScrollInfo);
public:
	bool OnScrollMessage(WPARAM ScrollingRequest);

	void SetRange(unsigned MaxRange);
	void UpdateVisibility(unsigned ScrollabelElementsCount);
	void inline SetPageSize(unsigned PageSize);

	unsigned GetPageSize() const;
	unsigned short GetPosition() const;

	void Initialize(HWND Parent, unsigned PageSize, unsigned Pages);
	CVerticalScroll();
};