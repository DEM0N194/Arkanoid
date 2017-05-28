#include "Brick.h"
#include <assert.h>

int Brick::lvl;

Brick::Brick(const RectF & rect_in,eBrickType brickType_in)
	:
	rect(rect_in),
	brickType(brickType_in),
	destroyed(false)
{
	switch (brickType)
	{
		case WHITE:
			bev = Beveler(Color(230, 230, 230));
			value = 50;
			break;
		case ORANGE:
			bev = Beveler(Color(230, 115, 0));
			value = 60;
			break;
		case CYAN:
			bev = Beveler(Color(0, 230, 230));
			value = 70;
			break;
		case GREEN:
			bev = Beveler(Color(0, 230, 0));
			value = 80;
			break;
		case RED:
			bev = Beveler(Color(230, 0, 0));
			value = 90;
			break;
		case BLUE:
			bev = Beveler(Color(0, 0, 230));
			value = 100;
			break;
		case MAGENTA:
			bev = Beveler(Color(230, 0, 230));
			value = 110;
			break;
		case YELLOW:
			bev = Beveler(Color(230, 230, 0));
			value = 120;
			break;
		case SILVER:
			bev = Beveler(Color(115, 115, 115));
			value = 50*lvl;
			life = 2 + lvl/8;
			break;
		case GOLD:
			bev = Beveler(Color(170, 170, 0));
			value = 0;
			life = 0;
			break;
	}
}

void Brick::Draw(Graphics & gfx) const
{
	if (!destroyed || brickType == GOLD)
	{
		bev.DrawBeveledBrick(rect.GetExpanded((brickType == GOLD || brickType == SILVER) ? -0.5f*padding : -1.0f*padding),
			(brickType == GOLD || brickType == SILVER) ? int(2.5f*bevelSize) : bevelSize, gfx);
	}
}

bool Brick::CheckBallCollision(const Ball & ball) const
{
	return (!destroyed || brickType == GOLD) && rect.IsOverlappingWith(ball.GetRect());
}

bool Brick::ExecuteBallCollision(Ball & ball)
{
	assert(CheckBallCollision(ball));
	const Vec2 ballPos = ball.GetPosition();
	if (signbit(ball.GetVelocity().x) == signbit( (ballPos.x - GetCenter().x) ))
	{
		ball.ReboundY();
	}
	else if (ballPos.x <= rect.right && ballPos.x >= rect.left)
	{
		ball.ReboundY();
	}
	else
	{
		ball.ReboundX();
	}
	life = max(life--, 0);
	if (life == 0)
	{
		destroyed = true;
		return true;
	}
	return false;
}

Vec2 Brick::GetCenter() const
{
	return rect.GetCenter();
}

int Brick::GetValue() const
{
	return value;
}

void Brick::SetLevel(int lvl_in)
{
	lvl = lvl_in;
}
