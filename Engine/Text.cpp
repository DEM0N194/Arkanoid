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
	box2 = {Graphics::ScreenWidth-1, Graphics::ScreenHeight-1};
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

void Text::Draw(Graphics& gfx)
{
	Position PosOld = pos;
	int row = 0;
	column = 0;
	pos.x = box1.x + PosOld.x;
	for (auto& ch : text)
	{
		if (!(pos.x + column < box2.x - 2* 25))
		{
			column = 0;
			row++;
		}
		pos.y = box1.y + PosOld.y + row * lineSpacing;
		if (ch == '\n')
		{
			column = 0;
			row++;
		}
		else
		{
			if(pos.y < box2.y - lineSpacing)
			DrawCh(ch, gfx);
		}
	}
	pos = PosOld;
}

void Text::DrawCh(char ch, Graphics& gfx)
{
	switch (ch)
	{
		case 'A':
			column += spacing + 25;
			gfx.chA(pos.x + column, pos.y, c);
			break;
		case 'B':
			column += spacing + 25;
			gfx.chB(pos.x + column, pos.y, c);
			break;
		case 'C':
			column += spacing + 25;
			gfx.chC(pos.x + column, pos.y, c);
			break;
		case 'D':
			column += spacing + 25;
			gfx.chD(pos.x + column, pos.y, c);
			break;
		case 'E':
			column += spacing + 25;
			gfx.chE(pos.x + column, pos.y, c);
			break;
		case 'F':
			column += spacing + 25;
			gfx.chF(pos.x + column, pos.y, c);
			break;
		case 'G':
			column += spacing + 25;
			gfx.chG(pos.x + column, pos.y, c);
			break;
		case 'H':
			column += spacing + 25;
			gfx.chH(pos.x + column, pos.y, c);
			break;
		case 'I':
			column += spacing + 25;
			gfx.chI(pos.x + column, pos.y, c);
			break;
		case 'J':
			column += spacing + 25;
			gfx.chJ(pos.x + column, pos.y, c);
			break;
		case 'K':
			column += spacing + 25;
			gfx.chK(pos.x + column, pos.y, c);
			break;
		case 'L':
			column += spacing + 25;
			gfx.chL(pos.x + column, pos.y, c);
			break;
		case 'M':
			column += spacing + 25;
			gfx.chM(pos.x + column, pos.y, c);
			break;
		case 'N':
			column += spacing + 25;
			gfx.chN(pos.x + column, pos.y, c);
			break;
		case 'O':
			column += spacing + 25;
			gfx.chO(pos.x + column, pos.y, c);
			break;
		case 'P':
			column += spacing + 25;
			gfx.chP(pos.x + column, pos.y, c);
			break;
		case 'Q':
			column += spacing + 25;
			gfx.chQ(pos.x + column, pos.y, c);
			break;
		case 'R':
			column += spacing + 25;
			gfx.chR(pos.x + column, pos.y, c);
			break;
		case 'S':
			column += spacing + 25;
			gfx.chS(pos.x + column, pos.y, c);
			break;
		case 'T':
			column += spacing + 25;
			gfx.chT(pos.x + column, pos.y, c);
			break;
		case 'U':
			column += spacing + 25;
			gfx.chU(pos.x + column, pos.y, c);
			break;
		case 'V':
			column += spacing + 25;
			gfx.chV(pos.x + column, pos.y, c);
			break;
		case 'W':
			column += spacing + 25;
			gfx.chW(pos.x + column, pos.y, c);
			break;
		case 'X':
			column += spacing + 25;
			gfx.chX(pos.x + column, pos.y, c);
			break;
		case 'Y':
			column += spacing + 25;
			gfx.chY(pos.x + column, pos.y, c);
			break;
		case 'Z':
			column += spacing + 25;
			gfx.chZ(pos.x + column, pos.y, c);
			break;
		case '0':
			column += spacing + 25;
			gfx.ch0(pos.x + column, pos.y, c);
			break;
		case '1':
			column += spacing + 15;
			gfx.ch1(pos.x + column, pos.y, c);
			break;
		case '2':
			column += spacing + 25;
			gfx.ch2(pos.x + column, pos.y, c);
			break;
		case '3':
			column += spacing + 25;
			gfx.ch3(pos.x + column, pos.y, c);
			break;
		case '4':
			column += spacing + 25;
			gfx.ch4(pos.x + column, pos.y, c);
			break;
		case '5':
			column += spacing + 25;
			gfx.ch5(pos.x + column, pos.y, c);
			break;
		case '6':
			column += spacing + 25;
			gfx.ch6(pos.x + column, pos.y, c);
			break;
		case '7':
			column += spacing + 25;
			gfx.ch7(pos.x + column, pos.y, c);
			break;
		case '8':
			column += spacing + 25;
			gfx.ch8(pos.x + column, pos.y, c);
			break;
		case '9':
			column += spacing + 25;
			gfx.ch9(pos.x + column, pos.y, c);
			break;
		case '.':
			column += spacing + 10;
			gfx.chDot(pos.x + column, pos.y, c);
			break;
		case ',':
			column += spacing + 10;
			gfx.chComma(pos.x + column, pos.y, c);
			break;
		case '\'':
			column += spacing + 5;
			gfx.chApostrophe(pos.x + column, pos.y, c);
			break;
		case '!':
			column += spacing + 5;
			gfx.chExMark(pos.x + column, pos.y, c);
			break;
		case '?':
			column += spacing + 25;
			gfx.chQMark(pos.x + column, pos.y, c);
			break;
		case '-':
			column += spacing + 15;
			gfx.chDash(pos.x + column, pos.y, c);
			break;
		default:
			column += spacing + 25;
			break;
	}
}
