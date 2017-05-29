#pragma once
#include "Graphics.h"
#include "Colors.h"
#include <string>

class Text
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
	Text();
	void Reset();
	void SetPostion(int in_x, int in_y);
	void SetColor(Color in_c);
	void SetColor(int r, int g, int b);
	void SetBoxSize(int x1, int y1, int x2, int y2);
	void SetSpacing(int in_spacing);
	void SetLineSpacing(int in_lineSpacing);
	void SetText(std::string in_text);
	void AlignLeft();
	void AlignMiddle();
	void AlignRight();
	void Draw(Graphics& gfx);
private:
	void DrawCh(char ch, Graphics& gfx);
	int GetLength(std::string s);
private:
	Color c;
	Position pos;
	Position box1;
	Position box2;
	Alignment alignment;
	std::string text;
	int column;
	int spacing;
	int lineSpacing;
};