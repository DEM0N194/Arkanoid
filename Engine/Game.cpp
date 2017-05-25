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
	walls(20.0f, float(gfx.ScreenWidth)-20.0f, 100.0f, float(gfx.ScreenHeight)),
	ball(Vec2(150, 250), Vec2(200, 200)),
	paddle(Vec2(400,850), 100, 10),
	soundPad(L"Sounds\\arkpad.wav"),
	soundBrick(L"Sounds\\fho.wav")
{
	const Color colors[4] = {Colors::Magenta, Colors::Cyan, Colors::Yellow, Colors::Green};
	const Vec2 topLeft(20.0f, 150.0f);
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
	float elapsedTime = ft.Mark();
	while (elapsedTime > 0.0f)
	{	
		const float dt = std::min(0.0025f, elapsedTime);
		UpdateModel(dt);
		elapsedTime -= dt;
	}
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel(float dt)
{
	paddle.Update(wnd.kbd, dt);
	paddle.DoWallCollision(walls);

	ball.Update(dt);

	bool collisionHappened = false;
	float curColDistSq;
	int curColIndex;
	for (int i = 0; i < nBricks; i++)
	{
		if (bricks[i].CheckBallCollision(ball))
		{
			const float newColDistSq = (ball.GetPosition() - bricks[i].GetCenter()).GetLengthSq();
			if (collisionHappened)
			{
				if (newColDistSq < curColDistSq)
				{
					curColDistSq = newColDistSq;
					curColIndex = i;
				}
			}
			else
			{
				curColDistSq = newColDistSq;
				curColIndex = i;
				collisionHappened = true;
			}
		}
	}

	if (collisionHappened)
	{
		paddle.ResetCooldown();
		bricks[curColIndex].ExecuteBallCollision(ball);
		//soundBrick.Play();
	}

	if (paddle.DoBallCollision(ball))
	{
		//soundPad.Play();
	}
	if (ball.DoWallCollisions(walls))
	{
		paddle.ResetCooldown();
		//soundPad.Play();
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
