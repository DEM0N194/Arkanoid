#include "LifeCounter.h"

LifeCounter::LifeCounter(Vec2 pos_in, int lives_in)
	:
	pos(pos_in + Vec2(padHalfWidth,padHalfHeight))
{
	SetLives(lives_in);
}

void LifeCounter::SetLives(int lives_in)
{
	lives = lives_in;
	const Vec2 offset(spacing + 2.0f*padHalfWidth, 0.0f);
	// I substract 1 form lives because we don't want to draw the last paddle,
	// because that's the paddle that the player is currently using
	for (int i = 0; i < lives-1; i++)
	{
		pads.push_back(Paddle(pos + offset*i, padHalfWidth, padHalfHeight));
	}
}

// returns true if u have no life
bool LifeCounter::ConsumeLife()
{
	lives--;
	if (lives > 0 && lives < 10)
	{
		pads.pop_back();
	}
	return lives == 0;
}

void LifeCounter::AddLife()
{
	const Vec2 offset(spacing + 2.0f*padHalfWidth, 0.0f);
	if (lives < 10)
	{
		pads.push_back(Paddle(pos + (offset * (lives-1) ), padHalfWidth, padHalfHeight));
	}
	lives++;
}

void LifeCounter::Draw(Graphics & gfx)
{
	for (int i = 0; i < pads.size(); i++)
	{
		pads.at(i).Draw(gfx);
	}
}
