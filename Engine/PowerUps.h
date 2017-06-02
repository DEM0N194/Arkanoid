#pragma once

#include "Graphics.h"
#include "Paddle.h"
#include "Ball.h"
#include <random>


// this is probably the worst way to do PowerUps, but hey it's working
class PowerUps
{
public:
	enum class Type
	{
		LASER,		// Red
		ENLARGE,	// Blue
		CATCH,		// Green
		SLOW,		// Orange
		BREAK,		// Magenta
		DISRUPTION,	// Cyan
		VAUS		// Grey
	};
private:
	class PowerUp
	{
	public:
		PowerUp(Vec2 pos, Type type, Paddle& paddle, Ball& ball);
		PowerUp& operator=(const PowerUp& rhs);
		bool Update(float dt);
		bool DoPaddleCollision();
		bool IsDestroyed() const;
		Type GetType() const;
		void DisablePowerUp();
		void Draw(Graphics& gfx) const;
	private:
		void ActivatePowerUp();
		RectF GetRect() const;
	private:
		Vec2 pos;
		Type type;
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
	void Gimme(Vec2 pos, Type type);
	void Draw(Graphics& gfx);
private:
	std::mt19937 rng;
	std::bernoulli_distribution spawnDist;
	Paddle& paddle;
	Ball& ball;
	std::vector<PowerUp> powerUps;
	int index2Delete;
	bool doDelete = false;
};