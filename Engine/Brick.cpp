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
	const Vec2 ballPos = ball.GetPosition();
	if (!destroyed && rect.IsOverlappingWith(ball.GetRect()))
	{
		if (ballPos.x <= rect.right && ballPos.x >= rect.left)
		{
			ball.ReboundY();
		}
		else
		{
			ball.ReboundX();
		}
		destroyed = true;
		return true;
	}
	return false;
}
