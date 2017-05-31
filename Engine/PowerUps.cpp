#include "PowerUps.h"

PowerUps::PowerUp::PowerUp(Vec2 pos_in, ePowerType type_in, Paddle& paddle_in)
	:
	pos(pos_in),
	type(type_in),
	paddle(paddle_in)
{
}

void PowerUps::PowerUp::Update(float dt)
{

	//? test code
	if (pos.y+height < Graphics::ScreenHeight)
	{
		pos.y += 200*dt;
	}
	else
	{
		destroyed = true;
	}
}

bool PowerUps::PowerUp::DoPaddleCollision()
{
	if (!destroyed && GetRect().IsOverlappingWith(paddle.GetRect()))
	{
		destroyed = true;
		inUse = true;
		return true;
	}
	return false;
}

void PowerUps::PowerUp::ActivatePowerUp()
{
	switch (type)
	{
		case ePowerType::Enlarge:
			paddle.Enlarge();
	}
}

void PowerUps::PowerUp::DisablePowerUp()
{
	switch (type)
	{
		case ePowerType::Enlarge:
			paddle.Shrink();
	}
}

bool PowerUps::PowerUp::IsInUse() const
{
	return destroyed && inUse;
}

void PowerUps::PowerUp::Draw(Graphics & gfx)
{
	if (!destroyed)
	{
		gfx.DrawCircle(pos.x + height/2, pos.y + height/2, height/2+1, Colors::Cyan);
		gfx.DrawCircle(pos.x + width - height/2, pos.y + height/2, height/2+1, Colors::Cyan);
		gfx.DrawRect(pos.x + height/2, pos.y, pos.x + width - height/2, pos.y + height, Colors::Cyan);
	}
}

RectF PowerUps::PowerUp::GetRect() const
{
	return RectF(pos,width, height);
}

PowerUps::PowerUp::~PowerUp()
{
	if (inUse)
	{
		DisablePowerUp();
	}
}
