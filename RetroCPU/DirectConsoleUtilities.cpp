#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "DirectConsoleUtilities.h"

DirectConsoleBufferSize::DirectConsoleBufferSize(short VisibleRows, short VisibleColumns, short Pages) :
	VisibleRows(VisibleRows),
	VisibleColumns(VisibleColumns),
	Pages(Pages)
{
	if(Pages < 1)
		Pages = 1;
}

DirectConsoleChar::DirectConsoleChar(wchar_t Char, int ForegroundColor, int BackgroundColor) :
	Char(Char),
	ForegroundColor(ForegroundColor),
	BackgroundColor(BackgroundColor)
{}

bool CDirectConsoleCursor::IsAtEndOfLine() const
{
	return (Position.X == (pLinkedBufferSize->VisibleColumns - 1));
}

bool CDirectConsoleCursor::IsLastChangeCorrect() const
{
	return (XLastChangeCorrect && YLastChangeCorrect);
}

DirectConsoleChar& CDirectConsoleCursor::GetChar(DirectConsoleChar** Buffer) const
{
	return Buffer[Position.Y][Position.X];
}

unsigned CDirectConsoleCursor::GetOffset() const
{
	return (Position.Y * pLinkedBufferSize->VisibleColumns) + Position.X;
}

short CDirectConsoleCursor::GetY() const
{
	return Position.Y;
}

void CDirectConsoleCursor::SetY(short NewY)
{
	Position.Y = NewY;
	if(Position.Y >= (pLinkedBufferSize->VisibleRows * pLinkedBufferSize->Pages))
		Position.Y = (pLinkedBufferSize->VisibleRows * pLinkedBufferSize->Pages) - 1;
	else if(Position.Y < 0)
		Position.Y = 0;
	YLastChangeCorrect = (Position.Y == NewY);
}

short CDirectConsoleCursor::GetX() const
{
	return Position.X;
}

void CDirectConsoleCursor::SetX(short NewX)
{
	Position.X = NewX;
	if(Position.X >= pLinkedBufferSize->VisibleColumns)
		Position.X = pLinkedBufferSize->VisibleColumns - 1;
	else if(Position.X < 0)
		Position.X = 0;
	XLastChangeCorrect = (Position.X == NewX);
}

void CDirectConsoleCursor::ToNextLine()
{
	int TotalRows = pLinkedBufferSize->VisibleRows * pLinkedBufferSize->Pages;
	if(Position.Y < (TotalRows - 1))
		++Position.Y;
	else
	{
		Position.Y = 0;
		XLastChangeCorrect = YLastChangeCorrect = false;
	}
	Position.X = 0;
}

void CDirectConsoleCursor::IncrementTotal()
{
	if(Position.X < (pLinkedBufferSize->VisibleColumns - 1))
		++Position.X;
	else
		ToNextLine();
}

void CDirectConsoleCursor::IncrementVisible()
{
	if(Position.X < (pLinkedBufferSize->VisibleColumns - 1))
		++Position.X;
	else
	{
		if(Position.Y < (pLinkedBufferSize->VisibleRows - 1))
			++Position.Y;
		else
		{
			Position.Y = 0;
			XLastChangeCorrect = YLastChangeCorrect = false;
		}
		Position.X = 0;
	}
}

void CDirectConsoleCursor::SetPosition(COORD& NewPosition)
{
	SetX(NewPosition.X);
	SetY(NewPosition.Y);
}

void CDirectConsoleCursor::LinkToBuffer(DirectConsoleBufferSize* pLinkedBufferSize)
{
	this->pLinkedBufferSize = pLinkedBufferSize;
}

CDirectConsoleCursor::CDirectConsoleCursor(DirectConsoleBufferSize* pLinkedBufferSize) :
	Position({ 0, 0 }),
	pLinkedBufferSize(pLinkedBufferSize),
	XLastChangeCorrect(true),
	YLastChangeCorrect(true)
{}