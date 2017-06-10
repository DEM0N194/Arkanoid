#include "Laser.h"

Laser::Ray::Ray(const RectF & rect_in)
	: rect(rect_in)
{
}

void Laser::Ray::Update(float dt)
{
	rect.top -= speed*dt;
	rect.bottom -= speed*dt;
}

RectF Laser::Ray::GetRect() const
{
	return rect;
}

void Laser::Ray::Draw(Graphics & gfx) const
{
	gfx.DrawRect(rect, Color(130, 50, 50));
}

Laser::Laser(Paddle & paddle_in, const Walls& walls_in)
	: paddle(paddle_in), walls(walls_in)
{
	DestroyLeft();
	DestroyRight();
}

void Laser::Update(float dt)
{
	if (paddle.LaserActive())
	{
		if (left != nullptr)
		{
			left->Update(dt);
			if (left->GetRect().top <= walls.GetInnerBounds().top)
			{
				DestroyLeft();
			}
		}
		if (right != nullptr)
		{
			right->Update(dt);
			if (right->GetRect().top <= walls.GetInnerBounds().top)
			{
				DestroyRight();
			}
		}
	}
	else
	{
		DestroyLeft();
		DestroyRight();
	}
}

RectF Laser::GetRectLeft() const
{
	if (left != nullptr)
	{
		return left->GetRect();
	}
	return paddle.GetRect();
}

RectF Laser::GetRectRight() const
{
	if (right != nullptr)
	{
		return right->GetRect();
	}
	return paddle.GetRect();
}

void Laser::DestroyLeft()
{
	left = nullptr;
}

void Laser::DestroyRight()
{
	right = nullptr;
}

void Laser::Shoot()
{
	if (left == nullptr && right == nullptr)
	{
		left = std::make_unique<Ray>(paddle.GetRectLaserLeft());
		right = std::make_unique<Ray>(paddle.GetRectLaserRight());
	}
}

void Laser::Draw(Graphics & gfx) const
{
	if (left != nullptr)
	{
		left->Draw(gfx);
	}
	if (right != nullptr)
	{
		right->Draw(gfx);
	}
}
