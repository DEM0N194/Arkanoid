/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	walls(0.0f, float(gfx.ScreenWidth), 0.0f, float(gfx.ScreenHeight)),
	ball(Vec2(100, 100), Vec2(200, 200)),
	paddle(Vec2(400,550), 100, 15),
	soundPad(L"Sounds\\arkpad.wav"),
	soundBrick(L"Sounds\\arkbrick.wav")
{
	const Color colors[4] = {Colors::Magenta, Colors::Cyan, Colors::Yellow, Colors::Green};
	const Vec2 topLeft(0.0f, 0.0f);
	for (int y = 0; y < nBricksDown; y++)
	{
		const Color c = colors[y];
		for (int x = 0; x < nBricksAcross; x++)
		{
			bricks[x + y * nBricksAcross] = Brick(RectF(topLeft + Vec2(x * brickWidth, y * brickHeight), brickWidth, brickHeight),c);
		}
	}
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dt = ft.Mark();

	paddle.Update(wnd.kbd, dt);
	paddle.DoWallCollision(walls);

	ball.Update(dt);

	for (Brick& b : bricks)
	{
		if (b.DoBallCollision(ball))
		{
			soundBrick.Play();
		}
	}

	if (paddle.DoBallCollision(ball))
	{
		soundPad.Play();
	}
	if (ball.DoWallCollisions(walls))
	{
		soundPad.Play();
	}
}

void Game::ComposeFrame()
{
	ball.Draw(gfx);
	for (const Brick& b : bricks)
	{
		b.Draw(gfx);
	}
	paddle.Draw(gfx);
}
