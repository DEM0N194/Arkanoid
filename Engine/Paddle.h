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
	void Draw(Graphics& gfx);
	void Update(Keyboard& kbd, float dt);
	bool DoBallCollision(Ball& ball);
	void DoWallCollision(const RectF& walls);
	RectF GetRect() const;
	Vec2 GetBallDir(Ball& ball);
	void ResetCooldown();
	void Destroy();
	void Restore();
	void Enlarge();
	void Shrink();
	void ActivateCatch();
	void DisableCatch();
	bool CatchActive();
	void CatchBall();
	void ReleaseBall();
	bool Catched();
private:
	void UpdateExitFactors();
	void FadeToColor(Beveler & beveler, Color goal);
private:
	Beveler bev;
	Beveler wingBev;
	Vec2 pos;
	float halfWidth;
	float enlargedHalfWidth;
	float halfHeight;
	float wingWidth;
	float exitXFactor;
	float fixedZoneHalfWidth;
	float fixedZoneExitX;
	float speed = 800.0f;
	bool enlarged = false;
	bool coolDown = false;
	bool destroyed = false;
	bool catchActive = false;
	bool catched = false;
};