#pragma once

#include "Graphics.h"
#include "Beveler.h"
#include "RectF.h"

class Walls
{
public:
	Walls(const RectF& innerBounds_in, int thickness_in, Color baseColor_in);
	const RectF& GetInnerBounds() const;
	void Draw( Graphics& gfx) const;
private:
	RectF innerBounds;
	int thickness;
	Beveler bev;
};