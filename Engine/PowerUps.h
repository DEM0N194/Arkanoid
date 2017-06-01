#pragma once

#include "Graphics.h"
#include "Paddle.h"
#include "Ball.h"
#include <random>

class PowerUps
{
public:
	enum class ePowerType
	{
		Laser,		// Red
		Enlarge,	// Blue
		Catch,		// Green
		Slow,		// Orange
		Break,		// Magenta
		Disruption,	// Cyan
		Vaus		// Grey
	};
private:
	class PowerUp
	{
	public:
		PowerUp(Vec2 pos, ePowerType type, Paddle& paddle, Ball& ball);
		PowerUp& operator=(const PowerUp& rhs);
		bool Update(float dt);
		bool DoPaddleCollision();
		bool IsDestroyed() const;
		ePowerType GetType() const;
		void DisablePowerUp();
		void Draw(Graphics& gfx) const;
	private:
		void ActivatePowerUp();
		RectF GetRect() const;
	private:
		Vec2 pos;
		ePowerType type;
		Color c;
		Paddle& paddle;
		Ball& ball;
		bool destroyed = false;
		static constexpr float width = 60.0f;
		static constexpr float halfHeight = 12.5f;
		static constexpr float speed = 200.0f;

	};
public:
	PowerUps(Paddle& paddle, Ball& ball);
	void Update(float dt);
	void Gimme(Vec2 pos, ePowerType type);
	void Draw(Graphics& gfx);
private:
	Paddle& paddle;
	Ball& ball;
	std::vector<PowerUp> powerUps;
	int index2Delete;
	bool doDelete = false;
};