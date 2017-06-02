#include "PowerUps.h"
#include <vector>

PowerUps::PowerUp::PowerUp(Vec2 pos_in, Type type_in, Paddle& paddle_in, Ball& ball_in)
	: pos(pos_in), type(type_in), paddle(paddle_in), ball(ball_in)
{
	switch (type) //TODO: add more colours
	{
		case Type::LASER:
			c = Colors::Red;
			break;
		case Type::ENLARGE:
			c = Colors::Blue;
			break;
		case Type::CATCH:
			c = Colors::Green;
			break;
		case Type::SLOW:
			c = Colors::Orange;
			break;
		case Type::DISRUPTION:
			c = Colors::Cyan;
			break;
		case Type::VAUS:
			c = Colors::Gray;
			break;
		case Type::BREAK:
			c = Colors::Magenta;
			break;
	}
}

PowerUps::PowerUp& PowerUps::PowerUp::operator=(const PowerUp & rhs)
{
	pos = rhs.pos;
	type = rhs.type;
	c = rhs.c;
	paddle = rhs.paddle;
	ball = rhs.ball;
	destroyed = rhs.destroyed;
	return *this;
}

 bool PowerUps::PowerUp::Update(float dt)
{

	//? test code
	if (pos.y + 2*halfHeight < Graphics::ScreenHeight)
	{
			pos.y += speed*dt;
			return true;
	}
	else
	{
		return false;
	}
}

bool PowerUps::PowerUp::DoPaddleCollision()
{
	if (GetRect().IsOverlappingWith(paddle.GetRect()))
	{
		ActivatePowerUp();
		destroyed = true;
		return true;
	}
	return false;
}

bool PowerUps::PowerUp::IsDestroyed() const
{
	return destroyed;
}

PowerUps::Type PowerUps::PowerUp::GetType() const
{
	return type;
}

void PowerUps::PowerUp::ActivatePowerUp()
{
	switch (type)
	{
		case Type::ENLARGE:
			paddle.Enlarge();
	}
}

void PowerUps::PowerUp::DisablePowerUp()
{
	switch (type)
	{
		case Type::ENLARGE:
			paddle.Shrink();
	}
}

void PowerUps::PowerUp::Draw(Graphics & gfx) const
{
	if (!destroyed)
	{
		gfx.DrawCircle(int(pos.x + halfHeight), int(pos.y + halfHeight), int(halfHeight+1), c);
		gfx.DrawCircle(int(pos.x + width - halfHeight), int(pos.y + halfHeight), int(halfHeight+1), c);
		gfx.DrawRect(int(pos.x + halfHeight), int(pos.y), int(pos.x + width - halfHeight), int(pos.y + 2*halfHeight), c);
	}
}

RectF PowerUps::PowerUp::GetRect() const
{
	return RectF(pos,width, 2*halfHeight);
}

PowerUps::PowerUps(Paddle & paddle_in, Ball & ball_in)
	: paddle(paddle_in), ball(ball_in), rng(std::random_device()()), spawnDist(0.2), typeDist(0,99)
{
}

void PowerUps::Update(float dt)
{
		for (int i = 0; i < powerUps.size(); i++)
		{
			if (powerUps.at(i).Update(dt))
			{
				if (powerUps.at(i).DoPaddleCollision())
				{
					if (powerUps.at(i).IsDestroyed() == true)
					{
						index2Delete = i-1;
						if (i-1 >= 0)
						{
							index2Delete = i-1;
							doDelete = true;
							if (powerUps.at(i-1).GetType() != powerUps.at(i).GetType())
							{
								powerUps.at(i-1).DisablePowerUp();
							}
						}
					}
				}
			}
			else
			{
				if (powerUps.at(i).IsDestroyed() == false)
				{
					index2Delete = i;
					doDelete = true;
				}
			}
		}
		if (doDelete)
		{
			powerUps.erase(powerUps.begin() + index2Delete);
			doDelete = false;
		}
}

void PowerUps::Gimme(Vec2 pos)
{
	//? Test Code Start
	pos.x = typeDist(rng) * 7.2 + 20;
	//? Test Coce End
	//if (spawnDist(rng))
	{
		const int currTypeDist = typeDist(rng);
		Type type;
		if (currTypeDist < 5)
		{
			type = Type::BREAK; // 5%
		}
		else if (currTypeDist < 20)
		{
			type = Type::VAUS; // 15%
		}
		else // 80%
		{
			type = Type(typeDist(rng)%5); // 20%
		}
		powerUps.push_back(PowerUp(pos, type, paddle, ball));
	}
}

void PowerUps::Draw(Graphics & gfx)
{
	for (auto& p : powerUps)
	{
		p.Draw(gfx);
	}
}
