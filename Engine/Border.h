#pragma once

#include "Walls.h"

class Border : public Walls
{
public:
	Border(const RectF& rect_in, int thickness_in)
		:
		Walls(rect_in,thickness_in)
	{
	}
	void Draw(Graphics& gfx) const
	{
		bev.DrawBeveledFrame(innerBounds.GetExpanded(float(thickness)), thickness/2, gfx);
	}
};