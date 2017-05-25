#include "Paddle.h"

Paddle::Paddle(const Vec2 & pos_in, float halfWidth_in, float halfHeight_in)
	:
	pos(pos_in),
	halfWidth(halfWidth_in),
	halfHeight(halfHeight_in)
{
	UpdateExitFactors();
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

bool Paddle::DoBallCollision(Ball & ball)
{
	if (!coolDown)
	{
		RectF rect(GetRect());
		if (rect.IsOverlappingWith(ball.GetRect()))
		{
			const Vec2 ballPos = ball.GetPosition();
			if (signbit(ball.GetVelocity().x) == signbit((ballPos.x - pos.x))
				|| (ballPos.x <= rect.right && ballPos.x >= rect.left))
			{
				Vec2 dir;
				const float xDifference = ballPos.x - pos.x;
				if (abs(xDifference) < fixedZoneHalfWidth)
				{
					if (xDifference < 0.0f)
					{
						dir = Vec2(-fixedZoneExitX, -1.0f);
					}
					else
					{
						dir = Vec2(fixedZoneExitX, -1.0f);
					}
				}
				else
				{
					dir = Vec2(xDifference * exitXFactor, -1.0f);
				}
				ball.SetDirection(dir);
			}
			else
			{
				ball.ReboundX();
			}
			coolDown = true;
			return true;
		}
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

void Paddle::ResetCooldown()
{
	coolDown = false;
}

void Paddle::UpdateExitFactors()
{
	exitXFactor = 1.2f/halfWidth;
	fixedZoneHalfWidth = halfWidth/4.0f;
	fixedZoneExitX = fixedZoneHalfWidth * exitXFactor;
}
