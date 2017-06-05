#include "Break.h"

Break::Break(float y_in)
	: y(y_in), topBev(Color(130, 50, 130)), botBev(Color(130, 50, 130))
{
	mid = RectF(float(Graphics::ScreenWidth - 20), float(Graphics::ScreenWidth), y, y);
	top = RectF(float(Graphics::ScreenWidth - 20), float(Graphics::ScreenWidth), y - 10, y);
	bot = RectF(float(Graphics::ScreenWidth - 20), float(Graphics::ScreenWidth), y, y + 10);
}

void Break::Update(float dt)
{
	if (open)
	{
		if (mid.top > y - 45)
		{
			mid.top -= 100*dt;
			top.bottom = mid.top;
			top.top = top.bottom - 15;
		}

		if (mid.bottom < y + 45)
		{
			mid.bottom += 100*dt;
			bot.top = mid.bottom;
			bot.bottom = bot.top + 15;
		}
	}
	else
	{
		if (mid.top <= y)
		{
			mid.top += 200*dt;
			top.bottom = mid.top;
			top.top = top.bottom - 15;
		}

		if (mid.bottom >= y)
		{
			mid.bottom -= 200*dt;
			bot.top = mid.bottom;
			bot.bottom = bot.top + 15;
		}
	}
}

void Break::Draw(Graphics & gfx) const
{
	if (mid.bottom >= y)
	{
		gfx.DrawRect(mid, Color(0, 0, 0));
		botBev.DrawBeveledBrick(bot, 5, gfx);
		topBev.DrawBeveledBrick(top, 5, gfx);
	}
}

void Break::Open()
{
	open = true;
}

void Break::Close()
{
	open = false;
}

bool Break::IsOpen() const
{
	return open;
}
