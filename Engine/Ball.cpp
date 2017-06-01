#include "Ball.h"

Ball::Ball(const Vec2 & pos_in, const Vec2 & dir_in)
	:
	pos(pos_in)
{
	SetDirection(dir_in);
}

void Ball::Draw(Graphics & gfx)
{
	SpriteCodex::DrawBall(pos, gfx);
}

void Ball::Update(float dt)
{
	pos += vel*dt;
}

Ball::Collision Ball::DoWallCollisions(const RectF& walls)
{
	const RectF rect = GetRect();
	Collision collision = Collision::NONE;
	if (rect.left < walls.left)
	{
		pos.x += walls.left - rect.left;
		ReboundX();
		collision = Collision::SIDE_TOP;
	}
	else if (rect.right > walls.right)
	{
		pos.x += walls.right - rect.right;
		ReboundX();
		collision = Collision::SIDE_TOP;
	}
	if (rect.top < walls.top)
	{
		pos.y += walls.top - rect.top;
		ReboundY();
		collision = Collision::SIDE_TOP;
	}
	else if (rect.bottom > walls.bottom)
	{
		pos.y += walls.bottom - rect.bottom;
		ReboundY();
		collision = Collision::BOTTOM;
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

void Ball::SetDirection(const Vec2 & dir)
{
	vel = dir.GetNormalized() * speed;
}

void Ball::ReboundX()
{
	vel.x = -vel.x;
}

void Ball::ReboundY()
{
	vel.y = -vel.y;
}
