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
//TODO:		Start - finish this when power ups are added
//TODO:		Ready - done
//TODO:		Play - done
//TODO:		End - finish this when scores are implemented
//TODO: make the look nice

//TODO: Levels
//TODO: win condition, go to next level
//TODO: PowerUps
//TODO: Sounds, possibly a sound manager

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	// Walls and borders
	walls(RectF(wallThickness, float(gfx.ScreenWidth)-wallThickness, float(gfx.ScreenHeight-fieldHeight), float(gfx.ScreenHeight)), int(wallThickness)),
	thinWalls(RectF(10, float(gfx.ScreenWidth)-10, float(gfx.ScreenHeight-fieldHeight)-10, float(gfx.ScreenHeight)), 10),
	infoWalls(RectF(10, float(gfx.ScreenWidth)-10, 10, float(gfx.ScreenHeight-fieldHeight)-10), int(10)),
	border(RectF(wallThickness, float(gfx.ScreenWidth)-wallThickness, wallThickness, float(gfx.ScreenHeight)-wallThickness), int(wallThickness)),
	infoBorder(RectF(10, float(gfx.ScreenWidth)-10, 10, float(gfx.ScreenHeight-fieldHeight)-wallThickness-10), 10),
	gameState(START)
{
	border.SetColor(Color(130, 130, 130));
	infoBorder.SetColor(Color(130, 130, 130));
	walls.SetColor(Color(0, 75, 150));
	thinWalls.SetColor(Color(0, 75, 150));
	infoWalls.SetColor(Color(0, 75, 150));
	lvl.SetNumOf0(1);
	highScore.SetPostion(410, 80);
	highScore.AlignMiddle();
	score.SetPostion(30, 80);

	InitializeText();
	ResetGame();
}

void Game::InitializeText()
{
	t_Title.SetText("ARKANOID");
	t_Title.SetPostion(250, 60);
	t_GameOver.SetText("GAME OVER");
	t_GameOver.SetPostion(250, 250);
	t_level.SetText("LEVEL");
	t_level.SetPostion(260, 500);
	t_lvl.SetText("LVL");
	t_lvl.SetPostion(670, 30);
	t_Ready.SetText("READY");
	t_Ready.SetPostion(300, 600);
	t_HighScore.SetText("HIGHSCORE");
	t_HighScore.SetPostion(250, 30);
	t_HighScore.SetColor(Colors::Red);
	t_Score.SetText("SCORE");
	t_Score.SetPostion(0, 30);
}

void Game::ResetGame()
{
	//ball = Ball(Vec2(150, 450), Vec2(300, 300));
	paddle = Paddle(Vec2(400, 810), 75, 10);
	life = LifeCounter(Vec2(30, 880), 3);

	lvl = 1;
	Brick::SetLevel(lvl.GetNum());
	score = 0;

	//TODO: move this code to lvl1					magenta			cyan		yellow			green
	const Brick::eBrickType brickTypes[5] = {Brick::SILVER, Brick::MAGENTA, Brick::CYAN, Brick::YELLOW, Brick::GREEN};
	const Vec2 topLeft(20.0f, 225.0f);
	for (int y = 0; y < nBricksDown; y++)
	{
		const Brick::eBrickType brickType = brickTypes[y];
		for (int x = 0; x < nBricksAcross; x++)
		{
			bricks[x + y * nBricksAcross] = Brick(RectF(topLeft + Vec2(x * brickWidth, y * brickHeight), brickWidth, brickHeight), brickType);
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
			Draw_Ready();
			break;
		case PLAY:
			Draw_Play();
			break;
		case END:
			if (currentWaitTime < 1.0f)
			{
				Draw_Play();
			}
			else
			{
				Draw_End();
			}
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
	paddle.Update(wnd.kbd, dt);
	paddle.DoWallCollision(walls.GetInnerBounds());

	// the ball sticks to the paddle
	ball = Ball(paddle.GetRect().GetCenter() + Vec2(50,-20),Vec2(0.6f,-1.0f));

	currentWaitTime += dt;
	if (currentWaitTime > readyWaitTime)
	{
		currentWaitTime = 0.0f;
		gameState = PLAY;
	}
	else if (currentWaitTime > readyWaitTime/2)
	{
		paddle.Restore();
	}
}

void Game::Game_Play(float dt)
{
	//? TEST CODE START
	if (wnd.kbd.KeyIsPressed(VK_SPACE))
	{
		if (!spacePressed)
		{
			life.ConsumeLife();
			lvl++;
			spacePressed = true;
		}
	}
	else
	{
		spacePressed = false;
	}
	//? TEST CODE END


	paddle.Update(wnd.kbd, dt);
	paddle.DoWallCollision(walls.GetInnerBounds());

	ball.Update(dt);

	// collision of the ball with the bricks
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
		// returns true if the brick is destroyed
		if (bricks[curColIndex].ExecuteBallCollision(ball))
		{
			// track scores
			score += bricks[curColIndex].GetValue();
			if (score > highScore)
			{
				highScore = score;
			}
		}
		//x sound for ball and brick collision goes here
	}

	// collision of the ball with the paddle
	if (paddle.DoBallCollision(ball))
	{
		//x sound for ball and paddle collsion goes here
	}

	// collision of the ball with the wall is handled here
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
		else
		{
			paddle.Destroy();
			gameState = READY;
		}
	}
}

void Game::Game_End(float dt)
{
	currentWaitTime += dt;
	if (currentWaitTime > 1.0f)
	{
		if (wnd.kbd.KeyIsPressed(VK_SPACE))
		{
			if (!spacePressed)
			{
				gameState = START;
				ResetGame();
				currentWaitTime = 0.0f;
				spacePressed = true;
			}
		}
		else
		{
			spacePressed = false;
		}
	}
	
}

void Game::Draw_Start()
{
	infoBorder.Draw(gfx);
	border.Draw(gfx);
	t_Title.Draw(gfx);
}

void Game::Draw_Ready()
{
	life.Draw(gfx);
	if (currentWaitTime > readyWaitTime/2)
	{
		ball.Draw(gfx);
		t_Ready.Draw(gfx);
	}
	paddle.Draw(gfx);
	for (const Brick& b : bricks)
	{
		b.Draw(gfx);
	}
	walls.Draw(gfx);
	thinWalls.Draw(gfx);
	infoWalls.Draw(gfx);
	
	// draw lvl in the infoWalls
	lvl.SetPostion(715, 80);
	lvl.Draw(gfx);
	t_lvl.Draw(gfx);
	// draw lvl in the middle of the screen
	lvl.SetPostion(460, 500);
	lvl.Draw(gfx);
	t_level.Draw(gfx);

	t_HighScore.Draw(gfx);
	highScore.Draw(gfx);
	t_Score.Draw(gfx);
	score.Draw(gfx);
}

void Game::Draw_Play()
{
	life.Draw(gfx);
	ball.Draw(gfx);
	for (const Brick& b : bricks)
	{
		b.Draw(gfx);
	}
	paddle.Draw(gfx);
	walls.Draw(gfx);
	thinWalls.Draw(gfx);
	infoWalls.Draw(gfx);

	// draw stuff in infoWalls
	t_lvl.Draw(gfx);
	lvl.SetPostion(715, 80);
	lvl.Draw(gfx);

	t_HighScore.Draw(gfx);
	highScore.Draw(gfx);
	t_Score.Draw(gfx);
	score.Draw(gfx);
}

void Game::Draw_End()
{
	infoBorder.Draw(gfx);
	t_Title.Draw(gfx);
	border.Draw(gfx);
	t_GameOver.Draw(gfx);
}
