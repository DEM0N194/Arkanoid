#pragma once

#include "Graphics.h"
#include "RectF.h"

class Beveler
{
public:
	Beveler() = default;
	Beveler(Color baseColor_in);
	void DrawOuterBevel(const RectF& rect, int size, Graphics& gfx) const;
	void DrawInnerBevel(const RectF& rect, int size, Graphics& gfx) const;
	void DrawBeveledBrick(const RectF& rect, int bevelSize, Graphics& gfx) const;
	void DrawBeveledFrame(const RectF& rect, int bevelSize, Graphics& gfx) const;
	void DrawBeveledFrameNoBottom(const RectF& rect, int bevelSize, Graphics& gfx) const;
	Color GetBaseColor() const;
	void SetBaseColor(Color baseColor_in);
private:
	void DrawOuterBevelNoBottom(const RectF& rect, int size, Graphics& gfx) const;
	void DrawInnerBevelNoBottom(const RectF& rect, int size, Graphics& gfx) const;
private:
	static constexpr float leftFactor = 1.10f;
	static constexpr float rightFactor = 0.65f;
	static constexpr float topFactor = 0.93f;
	static constexpr float bottomFactor = 0.80f;
	Color baseColor;
	Color leftColor;
	Color rightColor;
	Color topColor;
	Color bottomColor;
};