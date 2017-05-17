#include "Brick.h"

Brick::Brick(const RectF & rect_in, Color color_in)
	:
	rect(rect_in),
	color(color_in)
{
}

void Brick::Draw(Graphics & gfx) const
{
	if (!destroyed)
	{
		gfx.DrawRect(rect.GetExpanded(-padding), color);
	}
}

bool Brick::DoBallCollision(Ball & ball)
{
	RectF ballRect(ball.GetRect());
	float deltaX;
	float deltaY;
	if (!destroyed && rect.IsOverlappingWith(ballRect))
	{
		if (rect.left < ballRect.left)
		{
			deltaX = rect.right - ballRect.left;
		}
		else
		{
			deltaX = ballRect.right - rect.left;
		}
		if (rect.top < ballRect.top)
		{
			deltaY = rect.bottom - ballRect.top;
		}
		else
		{
			deltaY = ballRect.bottom - rect.top;
		}

		if (deltaX <= deltaY)
		{
			ball.ReboundX();
		}
		else
		{
			ball.ReboundY();
		}
		destroyed = true;
		return true;
	}
	return false;
}
