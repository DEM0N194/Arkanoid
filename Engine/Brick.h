#pragma once
#include "RectF.h"
#include "Colors.h"
#include "Graphics.h"
#include "Ball.h"
#include "Beveler.h"

class Brick
{
public:
	enum eBrickType
	{
		WHITE,		// 50
		ORANGE,		// 60
		CYAN,		// 70
		GREEN,		// 80
		RED,		// 90
		BLUE,		// 100
		MAGENTA,	// 110
		YELLOW,		// 120
		SILVER,		// 50*lvl (2 hit at begginig, +1 hit every 8 levels)
		GOLD,		// indestructable	-not counted
	};
public:
	Brick() = default;
	Brick(const RectF& rect_in, eBrickType BrickType_in);
	void Draw(Graphics& gfx) const;
	bool CheckBallCollision(const Ball& ball) const;
	bool ExecuteBallCollision(Ball& ball);
	Vec2 GetCenter() const;
	int GetValue() const;
	static void SetLevel(int lvl_in);
private:
	static constexpr float padding = 1.0f;
	static constexpr int bevelSize = 3;
	RectF rect;
	eBrickType brickType;
	Beveler bev;
	int value;
	int life = 1;
	static int lvl;
	bool destroyed;
};