#pragma once

#include "Graphics.h"
#include "Beveler.h"


class Break
{
public:
	Break() = default;
	Break(float y);
	void Update(float dt);
	void Draw(Graphics& gfx) const;
	void Open();
	void Close();
	bool IsOpen() const;
private:
	RectF top;
	RectF bot;
	RectF mid;
	Beveler topBev;
	Beveler botBev;
	float y = 810;
	bool open = false;
};