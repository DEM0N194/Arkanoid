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

//TODO: gamestates:
//TODO:		Start
//TODO:		Ready
//TODO:		Play
//TODO:		End

//TODO: Levels
//TODO: make the ball stick to the paddle during ready time and start from there
//TODO: Different kinds of bricks with different values
//TODO: Special bricks
//TODO: Score and HighScore Counter
//TODO: PowerUps
//TODO: Sounds, possibly a sound manager

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	// game objects
	walls(RectF(wallThickness, float(gfx.ScreenWidth)-wallThickness,float(gfx.ScreenHeight-fieldHeight), float(gfx.ScreenHeight)), int(wallThickness)),
	ball(Vec2(150, 450), Vec2(300, 300)),
	paddle(Vec2(400, 810), 75, 10),
	life(Vec2(30,880), 3),
	gameState(START)
{
	InitializeText();

	walls.SetColor(Color(0,50,200));
	const Color colors[4] = {Color(230,0,230), Color(0,230,230), Color(230,230,0), Color(0,230,0)};
	const Vec2 topLeft(20.0f, 225.0f);
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
	switch (gameState)
	{
		case START:
			Game_Start(dt);
			break;
		case READY:
			Game_Ready(dt);
			break;
		case PLAY:
			Game_Play(dt);
			break;
		case END:
			Game_End(dt);
			break;
	}
}

void Game::ComposeFrame()
{
	switch (gameState)
	{
		case START:
			Draw_Start();
			break;
		case READY:
			Draw_Game();
			break;
		case PLAY:
			Draw_Game();
			break;
		case END:
			Draw_End();
			break;
	}
}

void Game::Game_Start(float dt)
{
	if (wnd.kbd.KeyIsPressed(VK_SPACE))
	{
		if (!spacePressed)
		{
			gameState = READY;
			spacePressed = true;
		}
	}
	else
	{
		spacePressed = false;
	}
}

void Game::Game_Ready(float dt)
{
	gameState = PLAY;
}

void Game::Game_Play(float dt)
{
	paddle.Update(wnd.kbd, dt);
	paddle.DoWallCollision(walls.GetInnerBounds());

	ball.Update(dt);

	bool ball2brickCollisionHappened = false;
	float curColDistSq;
	int curColIndex;
	for (int i = 0; i < nBricks; i++)
	{
		if (bricks[i].CheckBallCollision(ball))
		{
			const float newColDistSq = (ball.GetPosition() - bricks[i].GetCenter()).GetLengthSq();
			if (ball2brickCollisionHappened)
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
				ball2brickCollisionHappened = true;
			}
		}
	}

	if (ball2brickCollisionHappened)
	{
		paddle.ResetCooldown();
		bricks[curColIndex].ExecuteBallCollision(ball);
		//x sound for ball and brick collision goes here
	}

	if (paddle.DoBallCollision(ball))
	{
		//x sound for ball and paddle collsion goes here
	}
	const int ball2wallCollsion = ball.DoWallCollisions(walls.GetInnerBounds());
	if (ball2wallCollsion == 1)
	{
		if (!paddle.GetRect().IsOverlappingWith(ball.GetRect()))
		{
			paddle.ResetCooldown();
		}
		//x Sound for ball and wall collision goes here
	}
	else if (ball2wallCollsion == 2)
	{
		// true if you consume your last life
		if (life.ConsumeLife())
		{
			gameState = END;
		}
	}
}

void Game::Game_End(float dt)
{
	if (wnd.kbd.KeyIsPressed(VK_SPACE))
	{
		if (!spacePressed)
		{
			gameState = START;
			spacePressed = true;
		}
	}
	else
	{
		spacePressed = false;
	}
}

void Game::Draw_Start()
{
	t_Title.Draw(gfx);
}

void Game::Draw_Game()
{
	life.Draw(gfx);
	ball.Draw(gfx);
	for (const Brick& b : bricks)
	{
		b.Draw(gfx);
	}
	paddle.Draw(gfx);
	walls.Draw(gfx);
}

void Game::Draw_End()
{
}

void Game::InitializeText()
{
	t_Title.SetText("ARKANOID");
	t_Title.SetPostion(250, 100);
	t_Title.SetColor(Colors::White);
}
