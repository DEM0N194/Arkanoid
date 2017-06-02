#pragma once

#include "Graphics.h"
#include "Paddle.h"
#include "Ball.h"
#include "LifeCounter.h"
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
		DISRUPTION,	// Cyan
		VAUS,		// Grey
		BREAK,		// Magenta
		INVALID
	};
private:
	class PowerUp
	{
	public:
		PowerUp(Vec2 pos, Type type, Paddle& paddle, Ball& ball, LifeCounter& life);
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
		LifeCounter& life;
		bool destroyed = false;
		static constexpr float halfWidth = 30.0f;
		static constexpr float halfHeight = 12.5f;
		static constexpr float speed = 200.0f;

	};
public:
	PowerUps(Paddle& paddle, Ball& ball, LifeCounter& life);
	void Update(int gs, float dt);
	void Gimme(Vec2 pos);
	void DisableCurrent();
	void DestroyAll();
	void Draw(Graphics& gfx);
private:
	std::mt19937 rng;
	std::bernoulli_distribution spawnDist;
	std::uniform_int_distribution<int> typeDist;
	Paddle& paddle;
	Ball& ball;
	LifeCounter& life;
	std::vector<PowerUp> powerUps;
	int index2Delete;
	bool doDelete = false;
};