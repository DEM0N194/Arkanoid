#include "Paddle.h"

Paddle::Paddle(const Vec2 & pos_in, float halfWidth_in, float halfHeight_in)
	:
	pos(pos_in),
	halfWidth(halfWidth_in),
	halfHeight(halfHeight_in),
	enlargedHalfWidth(1.5f*halfWidth),
	bev(Color(0, 0, 0)),
	wingBev(Color(0, 0, 0)),
	laserBotBev(Color(130, 130, 130)),
	laserLeftBev(Color(130, 130, 130)),
	laserRightBev(Color(130, 130, 130))

{
	UpdateExitFactors();
}

void Paddle::Draw(Graphics & gfx)
{
	if (laserActive)
	{
		FadeToColor(laserBotBev, Color(130, 50, 50));
		FadeToColor(laserLeftBev, Color(130, 50, 50));
		FadeToColor(laserRightBev, Color(130, 50, 50));
	}
	else
	{
		FadeToColor(laserBotBev, Color(130, 130, 130));
		FadeToColor(laserLeftBev, Color(130, 130, 130));
		FadeToColor(laserRightBev, Color(130, 130, 130));
	}

	RectF body = GetRect();
	RectF wingLeft = GetRect();
	wingWidth = (enlarged ? enlargedHalfWidth : halfWidth)/4;
	wingLeft.right -= (2* (enlarged ? enlargedHalfWidth : halfWidth) - wingWidth);
	RectF wingRight = GetRect();
	wingRight.left += (2* (enlarged ? enlargedHalfWidth : halfWidth) - wingWidth);
	bev.DrawBeveledBrick(body, 5, gfx);

	if (laserBotBev.GetBaseColor().GetG() > 50 && laserBotBev.GetBaseColor().GetG() < 120)
	{
		RectF laserBottom = body;
		laserBottom.top += halfHeight*1.5f;
		RectF laserLeft = body;
		laserLeft.left = pos.x - 30;
		laserLeft.right = pos.x - 25;
		RectF laserRight = body;
		laserRight.right = pos.x + 30;
		laserRight.left = pos.x + 25;
		laserLeftBev.DrawBeveledBrick(laserLeft, 2, gfx);
		laserRightBev.DrawBeveledBrick(laserRight, 2, gfx);
		laserBotBev.DrawBeveledBrick(laserBottom, 2, gfx);
	}


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
		if (laserActive)
		{
			FadeToColor(laserBotBev, Color(0, 0, 0));
			FadeToColor(laserLeftBev, Color(0, 0, 0));
			FadeToColor(laserRightBev, Color(0, 0, 0));
		}
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
				ball.SetDirection(GetBallDir(ball));
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

Vec2 Paddle::GetBallDir(Ball & ball)
{
	Vec2 dir;
	const float xDifference = ball.GetPosition().x - pos.x;
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
	return dir;
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
	if (!laserActive)
	{
		laserBotBev = Beveler(Color(130, 130, 130));
		laserLeftBev = Beveler(Color(130, 130, 130));
		laserRightBev = Beveler(Color(130, 130, 130));
	}
}

void Paddle::Enlarge()
{
	enlarged = true;
}

void Paddle::Shrink()
{
	enlarged = false;
}

void Paddle::ActivateCatch()
{
	catchActive = true;
}

void Paddle::DisableCatch()
{
	catchActive = false;
}

bool Paddle::CatchActive() const
{
	return catchActive;
}

void Paddle::CatchBall()
{
	catched = true;
}

void Paddle::ReleaseBall()
{
	catched = false;
}

bool Paddle::Catched() const
{
	return catched;
}

void Paddle::ActivateLaser()
{
	laserActive = true;
}

void Paddle::DisableLaser()
{
	laserActive = false;
}

bool Paddle::LaserActive() const
{
	return laserActive;
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
