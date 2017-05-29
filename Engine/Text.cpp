#include "Text.h"

Text::Text()
{
	Reset();
}

void Text::Reset()
{
	c = Colors::White;
	pos = {0,0};
	box1 = {0,0};
	box2 = {Graphics::ScreenWidth, Graphics::ScreenHeight};
	alignment = Left;
	text = "";
	spacing = 5;
	lineSpacing = 30 + 5;
}

void Text::SetPostion(int in_x, int in_y)
{
	pos.x = in_x;
	pos.y = in_y;
}

void Text::SetColor(Color in_c)
{
	c = in_c;
}

void Text::SetColor(int r, int g, int b)
{
	c = {unsigned char(r), unsigned char(g), unsigned char(b)};
}

void Text::SetBoxSize(int x1, int y1, int x2, int y2)
{
	box1.x = x1;
	box1.y = y1;
	box2.x = x2;
	box2.y = y2;
	if (x1 < 0) box1.x = 0;
	if (y1 < 0) box1.y = 0;
	if (x2 >= Graphics::ScreenWidth) box2.x = Graphics::ScreenWidth - 1;
	if (y2 >= Graphics::ScreenHeight) box2.y = Graphics::ScreenHeight - 1;
}

void Text::SetSpacing(int in_spacing)
{
	spacing = in_spacing;
}

void Text::SetLineSpacing(int in_lineSpacing)
{
	lineSpacing = 30 + in_lineSpacing;
}

void Text::SetText(std::string in_text)
{
	text = in_text;
	for (auto& c : text) c = toupper(c);
}

void Text::AlignLeft()
{
	alignment = Left;
}

void Text::AlignMiddle()
{
	alignment = Middle;
}

void Text::AlignRight()
{
	alignment = Right;
}

void Text::Draw(Graphics& gfx)
{
	Position PosOld = pos;
	int textLen = GetLength(text);
	int row = 0;
	column = 0;
	switch (alignment)
	{
		case Left:
			pos.x = box1.x + PosOld.x;
			break;
		case Middle:
			pos.x = (box2.x - box1.x)/2 + box1.x + PosOld.x - min(textLen/2, (box2.x - box1.x)/2);
			break;
		case Right:
			pos.x = box2.x + PosOld.x - min(textLen,box2.x - box1.x);
			break;
	}
	for (int i = 0; i < text.length(); i++)
	{
		switch (alignment)
		{
			case Left:
				if (!(pos.x + column < box2.x - 25))
				{
					column = 0;
					row++;
				}
				pos.y = box1.y + PosOld.y + row * lineSpacing;
				if (text[i] == '\n')
				{
					column = 0;
					row++;
				}
				else
				{
					if (pos.y < box2.y - lineSpacing)
					{
						DrawCh(text[i], gfx);
					}
				}
				break;
			case Middle:
				if (pos.x < box1.x)
				{
					pos.x = box1.x;
				}
				if (pos.x + column > box2.x - 25)
				{
					std::string newLine = text;
					newLine.erase(0, i-1);
					column = PosOld.x + (box2.x - box1.x)/2 - min(GetLength(newLine)/2,(box2.x - box1.x)/2);
					row++;
				}
				pos.y = box1.y + PosOld.y + row * lineSpacing;
				if (text[i] == '\n')
				{
					std::string newLine = text;
					newLine.erase(0, i+1);
					pos.x = (box2.x - box1.x)/2 + box1.x + PosOld.x - min(GetLength(newLine)/2, (box2.x - box1.x)/2);
					column = 0;
					row++;
				}
				else
				{
					if (pos.y < box2.y - lineSpacing)
					{
						DrawCh(text[i], gfx);
					}
				}
				break;
			case Right:
				std::string currCharStr(1, text[i]);
				if (pos.x + column + GetLength(currCharStr) > box2.x)
				{
					std::string newLine = text;
					newLine.erase(0, i);
					pos.x = (box2.x - box1.x) + box1.x + PosOld.x - min(GetLength(newLine), (box2.x - box1.x));
					column = 0;
					row++;
				}
				pos.y = box1.y + PosOld.y + row * lineSpacing;
				if (text[i] == '\n')
				{
					std::string newLine = text;
					newLine.erase(0, i+1);
					pos.x = (box2.x - box1.x) + box1.x + PosOld.x - min(GetLength(newLine), (box2.x - box1.x));
					column = 0;
					row++;
				}
				else
				{
					if (pos.y < box2.y - lineSpacing)
					{
						DrawCh(text[i], gfx);
					}
				}
				break;
		}
	}
	pos = PosOld;
}

void Text::DrawCh(char ch, Graphics& gfx)
{
	switch (ch)
	{
		case 'A':
			gfx.chA(pos.x + column, pos.y, c);
			column += spacing + 25;
			break;
		case 'B':
			gfx.chB(pos.x + column, pos.y, c);
			column += spacing + 25;
			break;
		case 'C':
			gfx.chC(pos.x + column, pos.y, c);
			column += spacing + 25;
			break;
		case 'D':
			gfx.chD(pos.x + column, pos.y, c);
			column += spacing + 25;
			break;
		case 'E':
			gfx.chE(pos.x + column, pos.y, c);
			column += spacing + 25;
			break;
		case 'F':
			gfx.chF(pos.x + column, pos.y, c);
			column += spacing + 25;
			break;
		case 'G':
			gfx.chG(pos.x + column, pos.y, c);
			column += spacing + 25;
			break;
		case 'H':
			gfx.chH(pos.x + column, pos.y, c);
			column += spacing + 25;
			break;
		case 'I':
			gfx.chI(pos.x + column, pos.y, c);
			column += spacing + 25;
			break;
		case 'J':
			gfx.chJ(pos.x + column, pos.y, c);
			column += spacing + 25;
			break;
		case 'K':
			gfx.chK(pos.x + column, pos.y, c);
			column += spacing + 25;
			break;
		case 'L':
			gfx.chL(pos.x + column, pos.y, c);
			column += spacing + 25;
			break;
		case 'M':
			gfx.chM(pos.x + column, pos.y, c);
			column += spacing + 25;
			break;
		case 'N':
			gfx.chN(pos.x + column, pos.y, c);
			column += spacing + 25;
			break;
		case 'O':
			gfx.chO(pos.x + column, pos.y, c);
			column += spacing + 25;
			break;
		case 'P':
			gfx.chP(pos.x + column, pos.y, c);
			column += spacing + 25;
			break;
		case 'Q':
			gfx.chQ(pos.x + column, pos.y, c);
			column += spacing + 25;
			break;
		case 'R':
			gfx.chR(pos.x + column, pos.y, c);
			column += spacing + 25;
			break;
		case 'S':
			gfx.chS(pos.x + column, pos.y, c);
			column += spacing + 25;
			break;
		case 'T':
			gfx.chT(pos.x + column, pos.y, c);
			column += spacing + 25;
			break;
		case 'U':
			gfx.chU(pos.x + column, pos.y, c);
			column += spacing + 25;
			break;
		case 'V':
			gfx.chV(pos.x + column, pos.y, c);
			column += spacing + 25;
			break;
		case 'W':
			gfx.chW(pos.x + column, pos.y, c);
			column += spacing + 25;
			break;
		case 'X':
			gfx.chX(pos.x + column, pos.y, c);
			column += spacing + 25;
			break;
		case 'Y':
			gfx.chY(pos.x + column, pos.y, c);
			column += spacing + 25;
			break;
		case 'Z':
			gfx.chZ(pos.x + column, pos.y, c);
			column += spacing + 25;
			break;
		case '0':
			gfx.ch0(pos.x + column, pos.y, c);
			column += spacing + 25;
			break;
		case '1':
			gfx.ch1(pos.x - 10 + column, pos.y, c);
			column += spacing + 15;
			break;
		case '2':
			gfx.ch2(pos.x + column, pos.y, c);
			column += spacing + 25;
			break;
		case '3':
			gfx.ch3(pos.x + column, pos.y, c);
			column += spacing + 25;
			break;
		case '4':
			gfx.ch4(pos.x + column, pos.y, c);
			column += spacing + 25;
			break;
		case '5':
			gfx.ch5(pos.x + column, pos.y, c);
			column += spacing + 25;
			break;
		case '6':
			gfx.ch6(pos.x + column, pos.y, c);
			column += spacing + 25;
			break;
		case '7':
			gfx.ch7(pos.x + column, pos.y, c);
			column += spacing + 25;
			break;
		case '8':
			gfx.ch8(pos.x + column, pos.y, c);
			column += spacing + 25;
			break;
		case '9':
			gfx.ch9(pos.x + column, pos.y, c);
			column += spacing + 25;
			break;
		case '.':
			gfx.chDot(pos.x - 15 + column, pos.y, c);
			column += spacing + 10;
			break;
		case ',':
			gfx.chComma(pos.x + 15 + column, pos.y, c);
			column += spacing + 10;
			break;
		case '\'':
			gfx.chApostrophe(pos.x - 20 + column, pos.y, c);
			column += spacing + 5;
			break;
		case '!':
			gfx.chExMark(pos.x - 20 + column, pos.y, c);
			column += spacing + 5;
			break;
		case '?':
			gfx.chQMark(pos.x + column, pos.y, c);
			column += spacing + 25;
			break;
		case '-':
			gfx.chDash(pos.x - 10 + column, pos.y, c);
			column += spacing + 15;
			break;
		default:
			column += spacing + 25;
			break;
	}
}

int Text::GetLength(std::string s)
{
	int length = 0;
	for (auto& ch : s)
	{
		switch (ch)
		{
			case '1':
				length += spacing + 15;
				break;
			case '.':
				length += spacing + 10;
				break;
			case ',':
				length += spacing + 10;
				break;
			case '!':
				length += spacing + 5;
				break;
			case '\'':
				length += spacing + 5;
				break;
			case '-':
				length += spacing + 15;
				break;
			case '\n':
				return length;
				break;
			default:
				length += spacing + 25;
				break;
		}
	}
	return length;
}
