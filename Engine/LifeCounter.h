#pragma once

#include "Paddle.h"
#include "Graphics.h"
#include <vector>

class LifeCounter
{
public:
	LifeCounter() = default;
	LifeCounter(Vec2 pos_in, int lives_in);
	bool ConsumeLife();
	void AddLife();
	void Draw(Graphics& gfx);
private:
	static constexpr float spacing = 11.0f;
	static constexpr float padHalfWidth = 33.0f;
	static constexpr float padHalfHeight = 5.0f;
	int lives;
	// pos origin upper left corner
	Vec2 pos;
	std::vector<Paddle> pads;
};