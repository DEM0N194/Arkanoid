#include "LifeCounter.h"

LifeCounter::LifeCounter(Vec2 pos_in, int lives_in)
	:
	pos(pos_in + Vec2(padHalfWidth,padHalfHeight)),
	lives(lives_in)
{
	const Vec2 offset(spacing + 2.0f*padHalfWidth, 0.0f);
	// I substract 1 form lives because we don't want to draw the last paddle,
	// because that's the paddle that the player is currently using
	for (int i = 0; i < lives-1; i++)
	{
		pads.push_back(Paddle(pos + offset*float(i), padHalfWidth, padHalfHeight));
	}
}

// returns true if u have no life
bool LifeCounter::ConsumeLife()
{
	lives = std::max(--lives, 0);
	if (lives > 0 && lives < 11)
	{
		pads.pop_back();
	}
	return lives == 0;
}

void LifeCounter::AddLife()
{
	const Vec2 offset(spacing + 2.0f*padHalfWidth, 0.0f);
	if (lives < 11)
	{
		pads.push_back(Paddle(pos + (offset * float(lives-1) ), padHalfWidth, padHalfHeight));
	}
	lives++;
}

void LifeCounter::Draw(Graphics & gfx)
{
	for (int i = 0; i < pads.size(); i++)
	{
		pads.at(i).Restore();
		pads.at(i).Draw(gfx);
	}
}
