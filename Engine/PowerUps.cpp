#include "PowerUps.h"
#include <vector>

PowerUps::PowerUp::PowerUp(Vec2 pos_in, Type type_in, Paddle& paddle_in, Ball& ball_in, LifeCounter& life_in)
	: pos(pos_in), type(type_in), paddle(paddle_in), ball(ball_in), life(life_in)
{
	switch (type)
	{
		case Type::LASER:
			c = Color(192, 64, 64); // Red
			break;
		case Type::ENLARGE:
			c = Color(64, 96, 192); // Blue
			break;
		case Type::CATCH:
			c = Color(64, 192, 64); // Green
			break;
		case Type::SLOW:
			c = Color(192, 128, 64); // Orange
			break;
		case Type::DISRUPTION:
			c = Color(64, 192, 192); // Cyan
			break;
		case Type::VAUS:
			c = Color(128, 128, 128);; // Gray
			break;
		case Type::BREAK:
			c = Color(192,64,192); // Magenta
			break;
		case Type::INVALID:
			destroyed = true;
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
	life = rhs.life;
	destroyed = rhs.destroyed;
	return *this;
}

 bool PowerUps::PowerUp::Update(float dt)
{
	if (pos.y + halfHeight < Graphics::ScreenHeight)
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
	if (!destroyed && GetRect().IsOverlappingWith(paddle.GetRect()))
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
		case Type::LASER:
			break;
		case Type::ENLARGE:
			paddle.Enlarge();
			break;
		case Type::CATCH:
			break;
		case Type::SLOW:
			break;
		case Type::DISRUPTION:
			break;
		case Type::VAUS:
			life.AddLife();
			break;
		case Type::BREAK:
			break;
	}
}

void PowerUps::PowerUp::DisablePowerUp()
{
	switch (type)
	{
		case PowerUps::Type::LASER:
			break;
		case PowerUps::Type::ENLARGE:
			paddle.Shrink();
			break;
		case PowerUps::Type::CATCH:
			break;
		case PowerUps::Type::SLOW:
			break;
		case PowerUps::Type::BREAK:
			break;
	}
}

void PowerUps::PowerUp::Draw(Graphics & gfx) const
{
	if (!destroyed)
	{
		gfx.DrawCircle(pos.x - halfWidth + halfHeight, pos.y, halfHeight, c);
		gfx.DrawCircle(pos.x + halfWidth - halfHeight, pos.y, halfHeight, c);

		RectF rect = GetRect();
		rect.left += halfHeight;
		rect.right -= halfHeight;
		gfx.DrawRect(rect, c);
	}
}

RectF PowerUps::PowerUp::GetRect() const
{
	return RectF::fromCenter(pos, halfWidth, halfHeight);
}

PowerUps::PowerUps(Paddle & paddle_in, Ball & ball_in, LifeCounter & life_in)
	: paddle(paddle_in), ball(ball_in), life(life_in)
	, rng(std::random_device()()), spawnDist(0.2), typeDist(0,99)
{
}

void PowerUps::Update(int gs, float dt)
{
		for (int i = 0; i < powerUps.size(); i++)
		{
			if (powerUps.at(i).Update(dt))
			{
				if (gs == 2 && powerUps.at(i).DoPaddleCollision())
				{
					index2Delete = i-1;
					if (i-1 >= 0 && powerUps.at(i-1).IsDestroyed() == true)
					{
						doDelete = true;
						if (powerUps.at(i-1).GetType() != powerUps.at(i).GetType())
						{
							powerUps.at(i-1).DisablePowerUp();
						}
					}
				}
				else if (powerUps.at(i).GetType() == Type::INVALID)
				{
					index2Delete = i-1;
					if (i-1 >= 0 && powerUps.at(i-1).IsDestroyed() == true)
					{
						doDelete = true;
						if (powerUps.at(i-1).GetType() != powerUps.at(i).GetType())
						{
							powerUps.at(i-1).DisablePowerUp();
						}
					}
					powerUps.erase(powerUps.begin() + i);
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


void PowerUps::DisableCurrent()
{
	powerUps.push_back(PowerUp(Vec2(100, 100), Type::INVALID, paddle, ball, life));
}

void PowerUps::DestroyAll()
{
	powerUps.clear();
}

void PowerUps::Gimme(Vec2 pos)
{
	if (spawnDist(rng))
	{
		const int currTypeDist = typeDist(rng);
		Type type;
		if (currTypeDist < 5)  // 5%
		{
			type = Type::BREAK;
		}
		else if (currTypeDist < 20) // 15%
		{
			type = Type::VAUS;
		}
		else // 80%
		{
			type = Type(typeDist(rng)%5); // 20%
		}
		powerUps.push_back(PowerUp(pos, type, paddle, ball, life));
	}
}

void PowerUps::Draw(Graphics & gfx)
{
	for (auto& p : powerUps)
	{
		p.Draw(gfx);
	}
}
