#pragma once

#include "Graphics.h"
#include "Paddle.h"
#include "Ball.h"

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
public:
	class PowerUp
	{
	public:
		PowerUp(Vec2 pos_in, ePowerType type_in, Paddle& paddle);
		void Update(float dt);
		bool DoPaddleCollision();
		void ActivatePowerUp();
		void DisablePowerUp();
		bool IsInUse() const;
		void Draw(Graphics& gfx);
		~PowerUp();
	private:
		RectF GetRect() const;
	private:
		Paddle& paddle;
		ePowerType type;
		bool destroyed = false;
		bool inUse = false;
		Vec2 pos;
		static constexpr float width = 60.0f;
		static constexpr float height = 25.0f;

	};
public:
	PowerUps(Ball& ball, Paddle& paddle);
	
};