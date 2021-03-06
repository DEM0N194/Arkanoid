#include "Brick.h"
#include <assert.h>

int Brick::lvl;

Brick::Brick(const RectF & rect_in,Type brickType_in)
	:
	rect(rect_in),
	brickType(brickType_in),
	destroyed(false),
	s_Brick(L"Sounds/Brick.mp3"),
	s_Silver(L"Sounds/Silver.mp3")
{
	switch (brickType)
	{
		case Type::WHITE:
			bev = Beveler(Color(230, 230, 230));
			value = 50;
			break;
		case Type::ORANGE:
			bev = Beveler(Color(230, 115, 0));
			value = 60;
			break;
		case Type::CYAN:
			bev = Beveler(Color(0, 230, 230));
			value = 70;
			break;
		case Type::GREEN:
			bev = Beveler(Color(0, 230, 0));
			value = 80;
			break;
		case Type::RED:
			bev = Beveler(Color(230, 0, 0));
			value = 90;
			break;
		case Type::BLUE:
			bev = Beveler(Color(0, 0, 230));
			value = 100;
			break;
		case Type::MAGENTA:
			bev = Beveler(Color(230, 0, 230));
			value = 110;
			break;
		case Type::YELLOW:
			bev = Beveler(Color(230, 230, 0));
			value = 120;
			break;
		case Type::SILVER:
			bev = Beveler(Color(115, 115, 115));
			value = 50*lvl;
			life = 2 + lvl/8;
			break;
		case Type::GOLD:
			bev = Beveler(Color(170, 170, 0));
			value = 0;
			life = 0;
			break;
	}
}

void Brick::Draw(Graphics & gfx) const
{
	if (!destroyed || brickType == Type::GOLD)
	{
		bev.DrawBeveledBrick(rect.GetExpanded((brickType == Type::GOLD || brickType == Type::SILVER) ? -0.5f*padding : -1.0f*padding),
			(brickType == Type::GOLD || brickType == Type::SILVER) ? int(2.5f*bevelSize) : bevelSize, gfx);
	}
}

bool Brick::CheckBallCollision(const Ball & ball) const
{
	return (!destroyed || brickType == Type::GOLD) && rect.IsOverlappingWith(ball.GetRect());
}

bool Brick::ExecuteBallCollision(Ball & ball)
{
	assert(CheckBallCollision(ball));

	ball.SetColor(bev.GetBaseColor());
	if (brickType == Type::SILVER)
	{
		Color c = bev.GetBaseColor();
		c.SetR(std::max((c.GetR() - 30), 25));
		c.SetG(std::max((c.GetG() - 30), 25));
		c.SetB(std::max((c.GetB() - 30), 25));
		bev = Beveler(c);

		s_Silver.Play();
	}
	else if(brickType == Type::GOLD)
	{
		s_Silver.Play();
	}
	else
	{
		s_Brick.Play();
	}

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

	life = std::max(--life, 0);
	if (life == 0)
	{
		destroyed = true;
		return true;
	}
	return false;
}

void Brick::ExecuteLaserCollision(Laser & laser)
{
	if (!destroyed || brickType == Type::GOLD)
	{
		if (rect.IsOverlappingWith(laser.GetRectLeft()))
		{
			laser.DestroyLeft();

			if (brickType == Type::SILVER)
			{
				Color c = bev.GetBaseColor();
				c.SetR(std::max((c.GetR() - 30), 25));
				c.SetG(std::max((c.GetG() - 30), 25));
				c.SetB(std::max((c.GetB() - 30), 25));
				bev = Beveler(c);
			}

			life = std::max(--life, 0);
			if (life == 0)
			{
				destroyed = true;
			}
		}
		if (rect.IsOverlappingWith(laser.GetRectRight()))
		{
			laser.DestroyRight();

			if (brickType == Type::SILVER)
			{
				Color c = bev.GetBaseColor();
				c.SetR(std::max((c.GetR() - 30), 25));
				c.SetG(std::max((c.GetG() - 30), 25));
				c.SetB(std::max((c.GetB() - 30), 25));
				bev = Beveler(c);
			}

			life = std::max(--life, 0);
			if (life == 0)
			{
				destroyed = true;
			}
		}
	}
}

Vec2 Brick::GetCenter() const
{
	return rect.GetCenter();
}

int Brick::GetValue() const
{
	return value;
}

bool Brick::IsDestroyed() const
{
	return destroyed;
}

void Brick::SetLevel(int lvl_in)
{
	lvl = lvl_in;
}
