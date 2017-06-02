#pragma once
#include "Vec2.h"
#include "Graphics.h"
#include "SpriteCodex.h"
#include <random>

class Ball
{
public:
	enum class Collision
	{
		NONE,
		SIDE_TOP,
		BOTTOM
	};
public:
	Ball() = default;
	Ball(const Vec2& pos_in, const Vec2& dir_in);
	void Draw(Graphics& gfx);
	void Update(float dt);
	Collision DoWallCollisions(const RectF& walls);
	void ReboundX();
	void ReboundY();
	RectF GetRect() const;
	Vec2 GetVelocity() const;
	Vec2 GetPosition() const;
	void SetDirection(const Vec2& dir);
	static void SpeedUp();
	static void SlowDown();
	static void ResetSpeed();
private:
	static constexpr float radius = 7.0f;
	static float speed;
	Vec2 pos;
	Vec2 vel;
	static std::random_device rd;
	static std::mt19937 rng;
	static std::uniform_real_distribution<float> sDist;
};