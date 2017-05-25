#include "Walls.h"
#include <cassert>

Walls::Walls(const RectF & innerBounds_in, int thickness_in)
	:
	innerBounds(innerBounds_in),
	thickness(thickness_in)
{
#ifndef NDEBUG
	innerBounds.bottom -= thickness;
#endif // !NDEBUG

	assert(thickness % 2 == 0);
	assert(innerBounds.GetExpanded(thickness).IsContainedBy(Graphics::GetScreenRect()));

#ifndef NDEBUG
	innerBounds.bottom += thickness;
#endif // !NDEBUG
}

const RectF & Walls::GetInnerBounds() const
{
	return innerBounds;
}

void Walls::Draw(Graphics & gfx) const
{
	bev.DrawBeveledFrameNoBottom(innerBounds.GetExpanded(float(thickness)), thickness/2, gfx);
}

void Walls::SetColor(Color c)
{
	bev.SetBaseColor(c);
}
