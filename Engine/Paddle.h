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
public: // powerups
	void Enlarge();
	void Shrink();
	void ActivateCatch();
	void DisableCatch();
	bool CatchActive() const;
	void CatchBall();
	void ReleaseBall();
	bool Catched() const;
	void ActivateLaser();
	void DisableLaser();
	bool LaserActive() const;
	RectF GetRectLaserLeft() const;
	RectF GetRectLaserRight() const;
private:
	void UpdateExitFactors();
	void FadeToColor(Beveler & beveler, Color goal);
	void AproachWidth(float goal, float dt);
	void AproachSpeed(float goal, float dt);
private:
	Beveler bev;
	Beveler wingBev;
	Beveler laserBotBev;
	Beveler laserLeftBev;
	Beveler laserRightBev;
	Vec2 pos;
	RectF laserLeft;
	RectF laserRight;
	float baseHalfWidth;
	float enlargedHalfWidth;
	float currentHalfWidth;
	float halfHeight;
	float wingWidth;
	float exitXFactor;
	float fixedZoneHalfWidth;
	float fixedZoneExitX;
	float speed = 0;
	bool enlarged = false;
	bool coolDown = false;
	bool destroyed = false;
	bool catchActive = false;
	bool catched = false;
	bool laserActive = false;
};