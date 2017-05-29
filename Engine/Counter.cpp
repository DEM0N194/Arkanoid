#include "Counter.h"
#include <string>

Counter::Counter()
{
	Reset();
}

void Counter::Reset()
{
	pos = {0,0};
	alignment = Left;
	c = Colors::White;
	num = 0;
	spacing = 5;
	numOf0 = 0;
}

void Counter::SetPostion(int x, int y)
{
	pos = {x,y};
}

void Counter::SetColor(Color in_c)
{
	c = in_c;
}

void Counter::SetColor(int r, int g, int b)
{
	c = {unsigned char(r), unsigned char(g), unsigned char(b)};
}

void Counter::SetSpacing(int in_spacing)
{
	spacing = in_spacing;
}

void Counter::SetNumOf0(int in_numOf0)
{
	numOf0 = in_numOf0;
}

void Counter::AlignLeft()
{
	alignment = Left;
}

void Counter::AlignMiddle()
{
	alignment = Middle;
}

void Counter::AlignRight()
{
	alignment = Right;
}

int Counter::GetNum() const
{
	return num;
}

void Counter::Draw(Graphics & gfx)
{
	Position posOld = pos;
	std::string snum = std::to_string(abs(num));
	for (int i = 0 + int(snum.size()); i <= numOf0; i++)
	{
		snum.insert(0, "0");
	}
	if (num < 0) snum.insert(0, "-");

	relativeXPos = 0;
	for (auto& ch : snum)
	{
		switch (alignment)
		{
			case Left:
				pos.x = posOld.x;
				break;
			case Middle:
				pos.x = posOld.x - GetLength(snum)/2;
				break;
			case Right:
				pos.x = posOld.x - GetLength(snum);
				break;
		}
		if (pos.x >= 0 &&
			pos.x + relativeXPos + 25 < gfx.ScreenWidth &&
			pos.y >= 0 &&
			pos.y + 30 < gfx.ScreenHeight)
		{
			DrawCh(ch, gfx);
		}
	}
	pos = posOld;
}

void Counter::DrawCh(char ch, Graphics & gfx)
{
	switch (ch)
	{
		case '0':
			gfx.ch0(pos.x + relativeXPos, pos.y, c);
			relativeXPos += spacing + 25;
			break;
		case '1':
			gfx.ch1(pos.x - 10 + relativeXPos, pos.y, c);
			relativeXPos += spacing + 15;
			break;
		case '2':
			gfx.ch2(pos.x + relativeXPos, pos.y, c);
			relativeXPos += spacing + 25;
			break;
		case '3':
			gfx.ch3(pos.x + relativeXPos, pos.y, c);
			relativeXPos += spacing + 25;
			break;
		case '4':
			gfx.ch4(pos.x + relativeXPos, pos.y, c);
			relativeXPos += spacing + 25;
			break;
		case '5':
			gfx.ch5(pos.x + relativeXPos, pos.y, c);
			relativeXPos += spacing + 25;
			break;
		case '6':
			gfx.ch6(pos.x + relativeXPos, pos.y, c);
			relativeXPos += spacing + 25;
			break;
		case '7':
			gfx.ch7(pos.x + relativeXPos, pos.y, c);
			relativeXPos += spacing + 25;
			break;
		case '8':
			gfx.ch8(pos.x + relativeXPos, pos.y, c);
			relativeXPos += spacing + 25;
			break;
		case '9':
			gfx.ch9(pos.x + relativeXPos, pos.y, c);
			relativeXPos += spacing + 25;
			break;
		case '-':
			gfx.chDash(pos.x - 10 + relativeXPos, pos.y, c);
			relativeXPos += spacing + 15;
			break;
	}
}

int Counter::GetLength(std::string snum)
{
	int length = 25;
	for (auto& ch : snum)
	{
		switch (ch)
		{
			case '1':
				length += spacing + 15;
				break;
			case '-':
				length += spacing + 15;
				break;
			default:
				length += spacing + 25;
				break;
		}
	}
	return length;
}

int Counter::operator+(int rhs)
{
	return num + rhs;
}

int Counter::operator+(const Counter & rhs)
{
	return num + rhs.num;
}

int Counter::operator-(int rhs)
{
	return num - rhs;
}

int Counter::operator-(const Counter & rhs)
{
	return num - rhs.num;
}

int Counter::operator*(int rhs)
{
	return num * rhs;
}

int Counter::operator*(const Counter & rhs)
{
	return num * rhs.num;
}

int Counter::operator/(int rhs)
{
	return num / rhs;
}

int Counter::operator/(const Counter & rhs)
{
	return num / rhs.num;
}

int Counter::operator%(int rhs)
{
	return num % rhs;
}

int Counter::operator%(const Counter & rhs)
{
	return num % rhs.num;
}

Counter Counter::operator++(int)
{
	return ++(*this);
}

Counter Counter::operator--(int)
{
	return --(*this);
}

Counter & Counter::operator++()
{
	++num;
	return *this;
}

Counter & Counter::operator--()
{
	--num;
	return *this;
}

Counter & Counter::operator=(int rhs)
{
	num = rhs;
	return *this;
}

Counter & Counter::operator=(const Counter & rhs)
{
	num = rhs.num;
	return *this;
}

Counter & Counter::operator+=(int rhs)
{
	num += rhs;
	return *this;
}

Counter & Counter::operator+=(const Counter & rhs)
{
	num += rhs.num;
	return *this;
}

Counter & Counter::operator-=(int rhs)
{
	num -= rhs;
	return *this;
}

Counter & Counter::operator-=(const Counter & rhs)
{
	num -= rhs.num;
	return *this;
}

Counter & Counter::operator*=(int rhs)
{
	num *= rhs;
	return *this;
}

Counter & Counter::operator*=(const Counter & rhs)
{
	num *= rhs.num;
	return *this;
}

Counter & Counter::operator/=(int rhs)
{
	num /= rhs;
	return *this;
}

Counter & Counter::operator/=(const Counter & rhs)
{
	num /= rhs.num;
	return *this;
}

Counter & Counter::operator%=(int rhs)
{
	num %= rhs;
	return *this;
}

Counter & Counter::operator%=(const Counter & rhs)
{
	num %= rhs.num;
	return *this;
}

bool Counter::operator<(int rhs)
{
	return num < rhs;
}

bool Counter::operator<(const Counter & rhs)
{
	return num < rhs.num;
}

bool Counter::operator>(int rhs)
{
	return num > rhs;
}

bool Counter::operator>(const Counter & rhs)
{
	return num > rhs.num;
}

bool Counter::operator<=(int rhs)
{
	return num <= rhs;
}

bool Counter::operator<=(const Counter & rhs)
{
	return num <= rhs.num;
}

bool Counter::operator>=(int rhs)
{
	return num >= rhs;
}

bool Counter::operator>=(const Counter & rhs)
{
	return num >= rhs.num;
}

bool Counter::operator==(int rhs)
{
	return num == rhs;
}

bool Counter::operator==(const Counter & rhs)
{
	return num == rhs.num;
}

bool Counter::operator!=(int rhs)
{
	return num != rhs;
}

bool Counter::operator!=(const Counter & rhs)
{
	return num != rhs.num;
}
