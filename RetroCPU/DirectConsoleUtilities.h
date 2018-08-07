#pragma once

#include <wincon.h>

inline unsigned Color(unsigned char R, unsigned char G, unsigned char B)
{
	return RGB(B, G, R);
}
inline bool IsNewLineChar(wchar_t Char)
{
	return (Char == L'\n') || (Char == L'\r') || (Char == '\r\n');
}

struct DirectConsoleBufferSize
{
	short VisibleRows;
	short VisibleColumns;
	short Pages;

	DirectConsoleBufferSize(short VisibleRows = 0, short VisibleColumns = 0, short Pages = 1);
};

struct DirectConsoleChar
{
	int ForegroundColor;
	int BackgroundColor;
	wchar_t Char;

	DirectConsoleChar(wchar_t Char = L' ', int ForegroundColor = -1, int BackgroundColor = -1);
};

class CDirectConsoleCursor
{
private:
	COORD Position;
	bool XLastChangeCorrect;
	bool YLastChangeCorrect;
	const DirectConsoleBufferSize* pLinkedBufferSize;
public:
	bool IsAtEndOfLine() const;
	bool IsLastChangeCorrect() const;
	DirectConsoleChar& GetChar(DirectConsoleChar** Buffer) const;
	unsigned GetOffset() const;
	short GetY() const;
	void SetY(short NewY);
	short GetX() const;
	void SetX(short NewX);
	void ToNextLine();
	void IncrementTotal();
	void IncrementVisible();
	void SetPosition(COORD& NewPosition);

	void LinkToBuffer(DirectConsoleBufferSize* pLinkedBufferSize);
	CDirectConsoleCursor(DirectConsoleBufferSize* pLinkedBufferSize = 0);
};