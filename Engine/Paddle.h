#pragma once

#include "Graphics.h"
#include "Keyboard.h"
#include "RectF.h"
#include "Beveler.h"
#include "Ball.h"

class Paddle
{
public:
	Paddle() = default;
	Paddle(const Vec2& pos_in, float halfWidth_in, float halfHeight_in);
	void Draw(Graphics& gfx) const;
	void Update(Keyboard& kbd, float dt);
	bool DoBallCollision(Ball& ball);
	void DoWallCollision(const RectF& walls);
	RectF GetRect() const;
	void ResetCooldown();
	void Destroy();
	void Restore();
private:
	void UpdateExitFactors();
	void FadeToColor(Color goal);
private:
	Beveler bev;
	Vec2 pos;
	float halfWidth;
	float halfHeight;
	float exitXFactor;
	float fixedZoneHalfWidth;
	float fixedZoneExitX;
	float speed = 650.0f;
	bool coolDown = false;
	bool destroyed = false;
};