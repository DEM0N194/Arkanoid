#include "Walls.h"
#include <cassert>

Walls::Walls(const RectF & innerBounds_in, int thickness_in, Color baseColor_in)
	:
	innerBounds(innerBounds_in),
	thickness(thickness_in),
	bev(baseColor_in)
{
	assert(innerBounds.GetExpanded(thickness).IsContainedBy(Graphics::GetScreenRect()));
}

const RectF & Walls::GetInnerBounds() const
{
	return innerBounds;
}

void Walls::Draw(Graphics & gfx) const
{
	bev.DrawBeveledFrameNoBottom(innerBounds.GetExpanded(float(thickness)), thickness, gfx);
}
