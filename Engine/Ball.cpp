#include "Ball.h"

Ball::Ball(const Vec2 & pos_in, const Vec2 & vel_in)
	:
	pos(pos_in),
	vel(vel_in)
{
}

void Ball::Draw(Graphics & gfx)
{
	SpriteCodex::DrawBall(pos, gfx);
}

void Ball::Update(float dt)
{
	pos += vel*dt;
}

bool Ball::DoWallCollisions(const RectF& walls)
{
	const RectF rect = GetRect();
	bool collided = false;
	if (rect.left < walls.left)
	{
		pos.x += walls.left - rect.left;
		ReboundX();
		collided = true;
	}
	else if (rect.right > walls.right)
	{
		pos.x += walls.right - rect.right;
		ReboundX();
		collided = true;
	}
	if (rect.top < walls.top)
	{
		pos.y += walls.top - rect.top;
		ReboundY();
		collided = true;
	}
	else if (rect.bottom > walls.bottom)
	{
		pos.y += walls.bottom - rect.bottom;
		ReboundY();
		collided = true;
	}
	return collided;
}

RectF Ball::GetRect() const
{
	return RectF::fromCenter(pos, radius, radius);
}

Vec2 Ball::GetVelocity() const
{
	return vel;
}

Vec2 Ball::GetPosition() const
{
	return pos;
}

void Ball::ReboundX()
{
	vel.x = -vel.x;
}

void Ball::ReboundY()
{
	vel.y = -vel.y;
}
