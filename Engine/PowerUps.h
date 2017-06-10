#pragma once

#include "Graphics.h"
#include "Paddle.h"
#include "Ball.h"
#include "LifeCounter.h"
#include "Sound.h"
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
		PowerUp(Vec2 pos, Type type, Paddle& paddle, LifeCounter& life);
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
		LifeCounter& life;
		bool destroyed = false;
		static constexpr float halfWidth = 30.0f;
		static constexpr float halfHeight = 12.5f;
		static constexpr float speed = 300.0f;
	};
public:
	class PowerUpIcon
	{
	public:
		PowerUpIcon(Vec2 pos, Type type);
		void Draw(Graphics& gfx) const;
	private:
		RectF GetRect() const;
	private:
		Vec2 pos;
		Type type;
		Color c;
		static constexpr float halfWidth = 30.0f;
		static constexpr float halfHeight = 12.5f;
	};
public:
	PowerUps(Paddle& paddle, LifeCounter& life);
	void Update(int gs, float dt);
	void Gimme(Vec2 pos);
	void DisableCurrent();
	void DestroyAll();
	void Draw(Graphics& gfx);
	static void DisableTriple();
	static void ActivateTriple();
	static bool TripleActive();
	static void TripleInit();
	static bool TripleInited();
private:
	std::mt19937 rng;
	std::bernoulli_distribution spawnDist;
	std::uniform_int_distribution<int> typeDist;
	Paddle& paddle;
	LifeCounter& life;
	std::vector<PowerUp> powerUps;
	int index2Delete;
	bool doDelete = false;
	static bool triple;
	static bool tripleInit;
	Sound s_Enlarge = Sound(L"Sounds/Enlarge.mp3");
	Sound s_Life = Sound(L"Sounds/Life.mp3");
	Sound s_default = Sound(L"Sounds/PowerUp.mp3");
};