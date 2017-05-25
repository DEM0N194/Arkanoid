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

int Ball::DoWallCollisions(const RectF& walls)
{
	const RectF rect = GetRect();
	int collision = 0;
	if (rect.left < walls.left)
	{
		pos.x += walls.left - rect.left;
		ReboundX();
		collision = 1;
	}
	else if (rect.right > walls.right)
	{
		pos.x += walls.right - rect.right;
		ReboundX();
		collision = 1;
	}
	if (rect.top < walls.top)
	{
		pos.y += walls.top - rect.top;
		ReboundY();
		collision = 1;
	}
	else if (rect.bottom > walls.bottom)
	{
		pos.y += walls.bottom - rect.bottom;
		ReboundY();
		collision = 2;
	}
	return collision;
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
