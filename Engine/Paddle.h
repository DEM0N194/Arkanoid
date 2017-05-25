#pragma once

#include "Graphics.h"
#include "Keyboard.h"
#include "RectF.h"
#include "Colors.h"
#include "Ball.h"

class Paddle
{
public:
	Paddle(const Vec2& pos_in, float halfWidth_in, float halfHeight_in);
	void Draw(Graphics& gfx) const;
	void Update(Keyboard& kbd, float dt);
	bool DoBallCollision(Ball& ball);
	void DoWallCollision(const RectF& walls);
	RectF GetRect() const;
	void ResetCooldown();
private:
	Color color = Colors::White;
	Vec2 pos;
	float halfWidth;
	float halfHeight;
	float speed = 450.0f;
	bool coolDown = false;
};