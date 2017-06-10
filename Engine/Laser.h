#pragma once

#include "Graphics.h"
#include "RectF.h"
#include "Paddle.h"
#include "Walls.h"
#include "Sound.h"
#include <memory>

class Laser
{
private:
	class Ray
	{
	public:
		Ray(const RectF& rect);
		void Update(float dt);
		RectF GetRect() const;
		void Draw(Graphics& gfx) const;
	private:
		RectF rect;
		static constexpr float speed = 700.0f;
	};
public:
	Laser(Paddle& paddle, const Walls& walls);
	void Update(float dt);
	RectF GetRectLeft() const;
	RectF GetRectRight() const;
	void DestroyLeft();
	void DestroyRight();
	void Shoot();
	void Draw(Graphics& gfx) const;
private:
	//Ray left;
	//Ray right;
	std::unique_ptr<Ray> left;
	std::unique_ptr<Ray> right;
	Paddle& paddle;
	const Walls& walls;
	Sound s_Laser;
};