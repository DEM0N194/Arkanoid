#include "Paddle.h"

Paddle::Paddle(const Vec2 & pos_in, float halfWidth_in, float halfHeight_in)
	:
	pos(pos_in),
	halfWidth(halfWidth_in),
	halfHeight(halfHeight_in),
	enlargedHalfWidth(1.5f*halfWidth),
	bev(Color(0,0,0)),
	wingBev(Color(0,0,0))
{
	UpdateExitFactors();
}

void Paddle::Draw(Graphics & gfx)
{
	RectF body = GetRect();
	RectF wingLeft = GetRect();
	wingWidth = (enlarged ? enlargedHalfWidth : halfWidth)/4;
	wingLeft.right -= (2* (enlarged ? enlargedHalfWidth : halfWidth) - wingWidth);
	RectF wingRight = GetRect();
	wingRight.left += (2* (enlarged ? enlargedHalfWidth : halfWidth) - wingWidth);
	bev.DrawBeveledBrick(body, 5, gfx);
	wingBev.DrawBeveledBrick(wingLeft, 5, gfx);
	wingBev.DrawBeveledBrick(wingRight, 5, gfx);
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

	if (destroyed)
	{
		FadeToColor(bev,Color(0, 0, 0));
		FadeToColor(wingBev, Color(0, 0, 0));
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
	return RectF::fromCenter(pos, enlarged ? enlargedHalfWidth : halfWidth, halfHeight);
}

void Paddle::ResetCooldown()
{
	coolDown = false;
}

void Paddle::Destroy()
{
	destroyed = true;
}

void Paddle::Restore()
{
	destroyed = false;
	FadeToColor(bev, Color(130, 130, 130));
	FadeToColor(wingBev, Color(130, 50, 50));
}

void Paddle::Enlarge()
{
	enlarged = true;
}

void Paddle::Shrink()
{
	enlarged = false;
}

void Paddle::UpdateExitFactors()
{
	exitXFactor = 1.2f/halfWidth;
	fixedZoneHalfWidth = halfWidth/4.0f;
	fixedZoneExitX = fixedZoneHalfWidth * exitXFactor;
}

void Paddle::FadeToColor(Beveler& beveler, Color goal)
{
	const Color current = beveler.GetBaseColor();
	Color updated = current;
	const int rDif = goal.GetR() - current.GetR();
	const int gDif = goal.GetG() - current.GetG();
	const int bDif = goal.GetB() - current.GetB();
	bool changed = false;

	if (rDif > 2)
	{
		updated.SetR(current.GetR()+2);
		changed = true;
	}
	if (rDif < -2)
	{
		updated.SetR(current.GetR()-2);
		changed = true;
	}

	if (gDif > 2 && rDif < gDif)
	{
		updated.SetG(current.GetG()+2);
		changed = true;
	}
	if (gDif < -2 && rDif > gDif)
	{
		updated.SetG(current.GetG()-2);
		changed = true;
	}

	if (bDif > 2 && rDif < bDif)
	{
		updated.SetB(current.GetB()+2);
		changed = true;
	}
	if (bDif < -2 && rDif > bDif)
	{
		updated.SetB(current.GetB()-2);
		changed = true;
	}

	if (changed)
	{
		beveler = Beveler(updated);
	}
}
