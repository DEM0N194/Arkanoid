#include "RectF.h"

RectF::RectF(float left_in, float right_in, float top_in, float bottom_in)
	:
	left(left_in),
	right(right_in),
	top(top_in),
	bottom(bottom_in)
{
}

RectF::RectF(const Vec2 & topLeft, const Vec2 & bottomRight)
	:
	RectF(topLeft.x, bottomRight.x, topLeft.y, bottomRight.y)
{
}

RectF::RectF(const Vec2 & topLeft, float width, float height)
	:
	RectF(topLeft, Vec2(topLeft.x + width, topLeft.y + height))
{
}

RectF RectF::GetExpanded(float offset) const
{
	return RectF(left - offset, right + offset, top - offset, bottom + offset);
}

Vec2 RectF::GetCenter() const
{
	return Vec2( (left + right)/2.0f, (top + bottom)/2.0f );
}

bool RectF::IsOverlappingWith(const RectF & other) const
{
	return left < other.right && right > other.left && top < other.bottom && bottom > other.top;
}

RectF RectF::fromCenter(const Vec2 & center, float halfWidth, float halfHeight)
{
	const Vec2 half(halfWidth, halfHeight);
	return RectF(center - half, center + half);
}
