#include "Paddle.h"

Paddle::Paddle(const Vec2 & pos_in, float halfWidth_in, float halfHeight_in)
	:
	pos(pos_in),
	halfWidth(halfWidth_in),
	halfHeight(halfHeight_in)
{
}

void Paddle::Draw(Graphics & gfx) const
{
	gfx.DrawRect(GetRect(), color);
}

void Paddle::Update(Keyboard & kbd, float dt)
{
	if (kbd.KeyIsPressed(VK_LEFT))
	{
		pos.x -= speed*dt;
	}
	if (kbd.KeyIsPressed(VK_RIGHT))
	{
		pos.x += speed*dt;
	}
}

bool Paddle::DoBallCollision(Ball & ball) const
{
	RectF ballRect(ball.GetRect());
	RectF rect(GetRect());
	float deltaX;
	float deltaY;
	if (rect.IsOverlappingWith(ballRect))
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
		return true;
	}
	return false;
}

void Paddle::DoWallCollision(const RectF & walls)
{
	RectF rect(GetRect());
	if (rect.left < walls.left)
	{
		pos.x += walls.left - rect.left;
	}
	else if (rect.right > walls.right)
	{
		pos.x += walls.right - rect.right;
	}
}

RectF Paddle::GetRect() const
{
	return RectF::fromCenter(pos, halfWidth, halfHeight);
}
