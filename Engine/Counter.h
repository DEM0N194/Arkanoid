#pragma once
#include "Graphics.h"
#include "Colors.h"

class Counter
{
private:
	struct Position
	{
		int x;
		int y;
	};
private:
	enum Alignment
	{
		Left,
		Middle,
		Right
	};
public:
	Counter();
	void Reset();
	void SetPostion(int x, int y);
	void SetColor(Color in_c);
	void SetColor(int r, int g, int b);
	void SetSpacing(int in_spacing);
	void SetNumOf0(int in_numOf0);
	void AlignLeft();
	void AlignMiddle();
	void AlignRight();
	void Draw(Graphics& gfx);
private:
	void DrawCh(char ch, Graphics& gfx);
public:
	int operator+(int rhs);
	int operator+(const Counter& rhs);
	int operator-(int rhs);
	int operator-(const Counter& rhs);
	int operator*(int rhs);
	int operator*(const Counter& rhs);
	int operator/(int rhs);
	int operator/(const Counter& rhs);
	int operator%(int rhs);
	int operator%(const Counter& rhs);
	Counter operator++(int); // T++
	Counter operator--(int); // T--
public:
	Counter& operator++(); // ++T
	Counter& operator--(); // --T
	Counter& operator=(int rhs);
	Counter& operator=(const Counter& rhs);
	Counter& operator+=(int rhs);
	Counter& operator+=(const Counter& rhs);
	Counter& operator-=(int rhs);
	Counter& operator-=(const Counter& rhs);
	Counter& operator*=(int rhs);
	Counter& operator*=(const Counter& rhs);
	Counter& operator/=(int rhs);
	Counter& operator/=(const Counter& rhs);
	Counter& operator%=(int rhs);
	Counter& operator%=(const Counter& rhs);
public:
	bool operator<(int rhs);
	bool operator<(const Counter& rhs);
	bool operator>(int rhs);
	bool operator>(const Counter& rhs);
	bool operator<=(int rhs);
	bool operator<=(const Counter& rhs);
	bool operator>=(int rhs);
	bool operator>=(const Counter& rhs);
	bool operator==(int rhs);
	bool operator==(const Counter& rhs);
	bool operator!=(int rhs);
	bool operator!=(const Counter& rhs);
private:
	Position pos;
	Alignment alignment;
	Color c;
	int num;
	int spacing;
	int numOf0;
};