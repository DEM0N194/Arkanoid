#include "Paddle.h"

Paddle::Paddle(const Vec2 & pos_in, float halfWidth_in, float halfHeight_in)
	:
	pos(pos_in),
	halfWidth(halfWidth_in),
	halfHeight(halfHeight_in),
	bev(Color(0,0,0))
{
	UpdateExitFactors();
}

void Paddle::Draw(Graphics & gfx) const
{
	bev.DrawBeveledBrick(GetRect(), 5, gfx);
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
		FadeToColor(Color(0, 0, 0));
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

void Paddle::Destroy()
{
	destroyed = true;
}

void Paddle::Restore()
{
	destroyed = false;
	FadeToColor(Color(130, 130, 130));
}

void Paddle::UpdateExitFactors()
{
	exitXFactor = 1.2f/halfWidth;
	fixedZoneHalfWidth = halfWidth/4.0f;
	fixedZoneExitX = fixedZoneHalfWidth * exitXFactor;
}

void Paddle::FadeToColor(Color goal)
{
	Color current = bev.GetBaseColor();
	Color updated;
	float rDif = goal.GetR() - current.GetR();
	float gDif = goal.GetG() - current.GetG();
	float bDif = goal.GetB() - current.GetB();
	bool changed = false;

	if (rDif > 2)
	{
		updated.SetR(current.GetR()+2);
		changed = true;
	}
	if (rDif < -1)
	{
		updated.SetR(current.GetR()-1);
		changed = true;
	}

	if (gDif > 2)
	{
		updated.SetG(current.GetG()+2);
		changed = true;
	}
	if (gDif < -1)
	{
		updated.SetG(current.GetG()-1);
		changed = true;
	}

	if (bDif > 2)
	{
		updated.SetB(current.GetB()+2);
		changed = true;
	}
	if (bDif < -1)
	{
		updated.SetB(current.GetB()-1);
		changed = true;
	}

	if (changed)
	{
		bev = Beveler(updated);
	}
}
