#pragma once
#include "Vec2.h"

class RectF
{
public:
	RectF() = default;
	RectF(float left_in, float right_in, float top_in, float bottom_in);
	RectF(const Vec2& topLeft, const Vec2& bottomRight);
	RectF(const Vec2& topLeft, float width, float height);
	RectF GetExpanded(float offset) const;
	Vec2 GetCenter() const;
	bool IsOverlappingWith(const RectF& other) const;
	bool IsContainedBy(const RectF& other) const;
	static RectF fromCenter(const Vec2& center, float halfWidth, float halfHeight);
public:
	float left;
	float right;
	float top;
	float bottom;
};