#include "Ball.h"
#include <algorithm>

float Ball::speed;
std::random_device Ball::rd;
std::mt19937 Ball::rng(rd());
std::uniform_real_distribution<float> Ball::sDist(0.0f, 15.0f);

Ball::Ball(const Ball & rhs, float angle)
	: Ball(rhs)
{
	Vec2 dir;
	dir.x = vel.x * cos(angle) - vel.y * sin(angle);
	dir.y = vel.x * sin(angle) + vel.y * cos(angle);
	SetDirection(dir);
}

Ball::Ball(const Vec2 & pos_in, const Vec2 & dir_in, Color c_in, Color cGoal_in)
	: pos(pos_in), c(c_in), cGoal(cGoal_in)
{
	SetDirection(dir_in);
}

void Ball::Draw(Graphics & gfx)
{
	UpdateColor();
	gfx.DrawCircle(pos.x, pos.y, 7.0f, c);
}

void Ball::Update(float dt)
{
	pos += vel * speed * dt;
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

void Ball::SetDirection(const Vec2 & dir_in)
{
	vel = dir_in.GetNormalized();
}

void Ball::SetPosition(const Vec2 & pos_in)
{
	pos = pos_in;
}

void Ball::SetColor(Color color)
{
	cGoal = color;
}

Color Ball::GetColor() const
{
	return c;
}

Color Ball::GetColorGoal() const
{
	return cGoal;
}

void Ball::PutInCoolDown()
{
	coolDown = true;
}

void Ball::ResetCoolDown()
{
	coolDown = false;
}

bool Ball::IsInCoolDown() const
{
	return coolDown;
}

void Ball::SpeedUp()
{
	speed += sDist(rng);
}

void Ball::SlowDown()
{
	speed = std::max(speed-100.0f,200.0f);
}

void Ball::ResetSpeed()
{
	speed = 500.0f;
}

void Ball::UpdateColor()
{
	Color updated = c;
	const int rDif = cGoal.GetR() - c.GetR();
	const int gDif = cGoal.GetG() - c.GetG();
	const int bDif = cGoal.GetB() - c.GetB();
	bool changed = false;
	constexpr int changeSpeed = 2;

	if (rDif > changeSpeed)
	{
		updated.SetR(c.GetR()+changeSpeed);
		changed = true;
	}
	if (rDif < -changeSpeed)
	{
		updated.SetR(c.GetR()-changeSpeed);
		changed = true;
	}

	if (gDif > changeSpeed)
	{
		updated.SetG(c.GetG()+changeSpeed);
		changed = true;
	}
	if (gDif < -changeSpeed)
	{
		updated.SetG(c.GetG()-changeSpeed);
		changed = true;
	}

	if (bDif > changeSpeed)
	{
		updated.SetB(c.GetB()+changeSpeed);
		changed = true;
	}
	if (bDif < -changeSpeed && rDif > bDif)
	{
		updated.SetB(c.GetB()-changeSpeed);
		changed = true;
	}

	if (changed)
	{
		c = updated;
	}
}

void Ball::ReboundX()
{
	vel.x = -vel.x;
}

void Ball::ReboundY()
{
	vel.y = -vel.y;
}
