#pragma once

#include "Graphics.h"
#include "Beveler.h"
#include "RectF.h"

class Walls
{
public:
	Walls(const RectF& innerBounds_in, int thickness_in);
	const RectF& GetInnerBounds() const;
	virtual void Draw( Graphics& gfx) const;
	void SetColor(const Color c);
	Color GetColor() const;
protected:
	int thickness;
	RectF innerBounds;
	Beveler bev;
};