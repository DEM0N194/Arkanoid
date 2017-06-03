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
#include "SpriteCodex.h"

//TODO: gamestates:
//TODO:		Start - done
//TODO:		Ready - done
//TODO:		Play - done
//TODO:		End - done
//TODo:		WIN - done
//TODO: make it look pretty

//TODO: PowerUps:
//TODO:		Laser		-Red
//TODO:		Enlarge		-Blue		- done
//TODO:		Catch		-Green		- done
//TODO:		Slow		-Orange		- done
//TODO:		Disruption	-Cyan
//TODO:		Vaus		-Grey		- done
//TODO:		Break		-Magenta

//TODO: add more Levels
//TODO: Sounds, possibly a sound manager
//TODO: fine tune brick colors
//TODO: fine tune the game speed so it's not as easy as it is now
//TODO: Add fireworks to WIN screen so it feels more rewarding xD

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	rng(std::random_device()()),
	rxDist(-45, 45),
	// Walls and borders
	walls(RectF(wallThickness, float(gfx.ScreenWidth)-wallThickness, float(gfx.ScreenHeight-fieldHeight), float(gfx.ScreenHeight)), int(wallThickness)),
	thinWalls(RectF(10, float(gfx.ScreenWidth)-10, float(gfx.ScreenHeight-fieldHeight)-10, float(gfx.ScreenHeight)), 10),
	infoWalls(RectF(10, float(gfx.ScreenWidth)-10, 10, float(gfx.ScreenHeight-fieldHeight)-10), int(10)),
	border(RectF(wallThickness, float(gfx.ScreenWidth)-wallThickness, wallThickness, float(gfx.ScreenHeight)-wallThickness), int(wallThickness)),
	infoBorder(RectF(10, float(gfx.ScreenWidth)-10, 10, float(gfx.ScreenHeight-fieldHeight)-wallThickness), 10),
	bottomBorder(RectF(10, float(gfx.ScreenWidth)-10, 680, float(gfx.ScreenHeight)-10), 10),
	gameState(START),
	powerUps(paddle, ball, life),
	p_Laser(Vec2(140,280),PowerUps::Type::LASER),
	p_Expand(Vec2(450,280), PowerUps::Type::ENLARGE),
	p_Catch(Vec2(140,360), PowerUps::Type::CATCH),
	p_Slow(Vec2(450,360), PowerUps::Type::SLOW),
	p_Triple(Vec2(140,440), PowerUps::Type::DISRUPTION),
	p_Vaus(Vec2(450,440), PowerUps::Type::VAUS)
{
	border.SetColor(Color(130, 130, 130));
	infoBorder.SetColor(Color(130, 130, 130));
	bottomBorder.SetColor(Color(130, 130, 130));
	walls.SetColor(Color(0, 75, 150));
	thinWalls.SetColor(Color(0, 75, 150));
	infoWalls.SetColor(Color(0, 75, 150));
	lvl.SetNumOf0(1);
	highScore.SetPostion(440, 80);
	highScore.AlignMiddle();

	InitializeText();
	ResetGame();
}

void Game::InitializeText()
{
	t_Title.SetText("ARKANOID");
	t_Title.SetPostion(0, 60);
	t_Title.AlignMiddle();
	t_GameOver.SetText("GAME OVER");
	t_GameOver.SetPostion(0, 250);
	t_GameOver.AlignMiddle();
	t_GameOver.SetColor(Colors::Red);
	t_YouWin.SetText("YOU WIN");
	t_YouWin.SetPostion(0, 250);
	t_YouWin.AlignMiddle();
	t_PressSpace.SetPostion(0, 550);
	t_PressSpace.AlignMiddle();
	t_DEM0N194.SetText("DEM0N194");
	t_DEM0N194.SetPostion(0, 760);
	t_DEM0N194.AlignMiddle();
	t_DEM0N194.SetColor(150, 150, 150);
	t_level.SetText("LEVEL");
	t_level.SetPostion(305, 500);
	t_lvl.SetText("LVL");
	t_lvl.SetPostion(700, 30);
	t_Ready.SetText("READY");
	t_Ready.SetPostion(0, 600);
	t_Ready.AlignMiddle();
	t_HighScore.SetText("HIGHSCORE");
	t_HighScore.SetPostion(290, 30);
	t_HighScore.SetColor(Colors::Red);
	t_Score.SetText("SCORE");
	t_Score.SetPostion(30, 30);
	t_L.SetText("L");
	t_Laser.SetText(" ASER");
	t_L.SetPostion(220, 280);
	t_Laser.SetPostion(220, 280);
	t_L.SetColor(130, 50, 50);
	t_E.SetText("E");
	t_Expand.SetText(" XPAND");
	t_E.SetPostion(530, 280);
	t_Expand.SetPostion(530, 280);
	t_E.SetColor(50, 50, 130);
	t_C.SetText("C");
	t_Catch.SetText(" ATCH");
	t_C.SetPostion(220, 360);
	t_Catch.SetPostion(220, 360);
	t_C.SetColor(50, 130, 50);
	t_S.SetText("S");
	t_Slow.SetText(" LOW");
	t_S.SetPostion(530, 360);
	t_Slow.SetPostion(530, 360);
	t_S.SetColor(130, 90, 50);
	t_T.SetText("T");
	t_Triple.SetText(" RIPLE");
	t_T.SetPostion(220, 440);
	t_Triple.SetPostion(220, 440);
	t_T.SetColor(50, 130, 130);
	t_V.SetText("V");
	t_Vaus.SetText(" AUS");
	t_V.SetPostion(530, 440);
	t_Vaus.SetPostion(530, 440);
	t_V.SetColor(130, 130, 130);
	t_PowerUps.SetText(" OWER UPS");
	t_PowerUps.SetPostion(0, 200);
	t_PowerUps.AlignMiddle();
	t_P.SetText("P        ");
	t_P.SetPostion(0, 200);
	t_P.AlignMiddle();
	t_P.SetColor(130, 50, 130);
	t_Thanks.SetText("THANK YOU FOR PLAYING!");
	t_Thanks.SetPostion(0, 430);
	t_Thanks.AlignMiddle();
	t_Thanks.SetColor(Colors::Gray);
}

void Game::ResetGame()
{
	Ball::ResetSpeed();
	paddle = Paddle(Vec2(410, 810), 60, 10);
	life = LifeCounter(Vec2(30, 880), 3);
	powerUps.DestroyAll();

	lvl = 1;
	score = 0;

	LoadLevel();
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
			Game_EndWin(dt);
			break;
		case WIN:
			Game_EndWin(dt);
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
		case WIN:
			if (currentWaitTime < 1.0f)
			{
				Draw_Play();
			}
			else
			{
				Draw_Win();
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
			ballRelativeX = rxDist(rng);
			spacePressed = true;
		}
	}
	else
	{
		spacePressed = false;
	}

	currentWaitTime += dt;
	if (currentWaitTime > 1.0f)
	{
		t_PressSpace.SetColor(Colors::White);
		currentWaitTime = 0.0f;
	}
	else if (currentWaitTime > 0.5f)
	{
		t_PressSpace.SetColor(Colors::Yellow);
	}
}

void Game::Game_Ready(float dt)
{
	paddle.Update(wnd.kbd, dt);
	paddle.DoWallCollision(walls.GetInnerBounds());
	powerUps.Update(gameState, dt);

	// the ball sticks to the paddle
	ball = Ball(paddle.GetRect().GetCenter() + Vec2(float(ballRelativeX),-17),paddle.GetBallDir(ball));

	currentWaitTime += dt;
	if (currentWaitTime > readyWaitTime)
	{
		currentWaitTime = 0.0f;
		gameState = PLAY;
	}
	else if (currentWaitTime > readyWaitTime/2)
	{
		powerUps.DisableCurrent();
		paddle.Restore();
	}
}

void Game::Game_Play(float dt)
{
	paddle.Update(wnd.kbd, dt);
	paddle.DoWallCollision(walls.GetInnerBounds());
	powerUps.Update(gameState, dt);

	if (paddle.Catched())
	{
		ball = Ball(paddle.GetRect().GetCenter() + Vec2(float(ballRelativeX), -17),paddle.GetBallDir(ball));
	}
	else
	{
		ball.Update(dt);
	}

	bool levelCleared = true;
	bool ball2brickCollisionHappened = false;
	float curColDistSq;
	int curColIndex;
	for (int i = 0; i < nBricks; i++)
	{
		// collision of the ball with the bricks
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
				powerUps.Gimme(bricks[i].GetCenter());
				Ball::SpeedUp();
			}
		}

		// if any of the bricks is not destroyed, the level is not cleared
		if (bricks[i].IsDestroyed() == false)
		{
			levelCleared = false;
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
		if (paddle.CatchActive())
		{
			paddle.CatchBall();
			ballRelativeX = int(ball.GetRect().GetCenter().x - paddle.GetRect().GetCenter().x);
		}
		//x sound for ball and paddle collsion goes here
	}

	// collision of the ball with the wall is handled here
	const Ball::Collision ball2wallCollsion = ball.DoWallCollisions(walls.GetInnerBounds());
	if (ball2wallCollsion == Ball::Collision::SIDE_TOP)
	{
		if (!paddle.GetRect().IsOverlappingWith(ball.GetRect()))
		{
			paddle.ResetCooldown();
		}
		//x Sound for ball and wall collision goes here
	}
	else if (ball2wallCollsion == Ball::Collision::BOTTOM)
	{
		// true if you consume your last life
		if (life.ConsumeLife())
		{
			gameState = END;
		}
		else
		{
			gameState = READY;
			paddle.Destroy();
			Ball::ResetSpeed();
			ballRelativeX = rxDist(rng);
		}
	}

	//? TEST CODE START
	if (wnd.kbd.KeyIsPressed(VK_SPACE))
	{
		if (!spacePressed)
		{
			//life.AddLife();
			//lvl++;
			//lvl = lvl == 2 ? 0 : 1;
			//levelCleared = true;
			powerUps.Gimme(Vec2(500, 300));
			if (paddle.Catched())
			{
				paddle.ReleaseBall();
			}
			spacePressed = true;
		}
	}
	else
	{
		spacePressed = false;
	}
	//? TEST CODE END

	//! LEVEL CLEARED
	if (levelCleared)
	{
		gameState = READY;
		paddle.Destroy();
		Ball::ResetSpeed();
		lvl++;
		LoadLevel();
	}
}

void Game::Game_EndWin(float dt)
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
	if (currentWaitTime > 2.0f)
	{
		t_PressSpace.SetColor(Colors::White);
		currentWaitTime = 1.0f;
	}
	else if (currentWaitTime > 1.5f)
	{
		t_PressSpace.SetColor(Colors::Yellow);
	}
}

void Game::Draw_Start()
{
	infoBorder.Draw(gfx);
	bottomBorder.Draw(gfx);
	border.Draw(gfx);

	t_Title.Draw(gfx);
	t_DEM0N194.Draw(gfx);

	t_PressSpace.SetText("Press Space to START");
	t_PressSpace.Draw(gfx);

	SpriteCodex::DrawLogo(Vec2(gfx.ScreenWidth-176-30, 690), gfx);
	SpriteCodex::DrawLogo(Vec2(30, 690), gfx);

	p_Laser.Draw(gfx);
	p_Expand.Draw(gfx);
	p_Catch.Draw(gfx);
	p_Slow.Draw(gfx);
	p_Triple.Draw(gfx);
	p_Vaus.Draw(gfx);

	t_Laser.Draw(gfx);
	t_L.Draw(gfx);
	t_Expand.Draw(gfx);
	t_E.Draw(gfx);
	t_Catch.Draw(gfx);
	t_C.Draw(gfx);
	t_Slow.Draw(gfx);
	t_S.Draw(gfx);
	t_Triple.Draw(gfx);
	t_T.Draw(gfx);
	t_Vaus.Draw(gfx);
	t_V.Draw(gfx);
	t_PowerUps.Draw(gfx);
	t_P.Draw(gfx);
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
	powerUps.Draw(gfx);
	for (const Brick& b : bricks)
	{
		b.Draw(gfx);
	}

	walls.Draw(gfx);
	thinWalls.Draw(gfx);
	infoWalls.Draw(gfx);
	
	// draw lvl in the infoWalls
	lvl.SetPostion(755, 80);
	lvl.AlignMiddle();
	lvl.Draw(gfx);
	t_lvl.Draw(gfx);
	// draw lvl in the middle of the screen
	lvl.SetPostion(550, 500);
	lvl.AlignRight();
	lvl.Draw(gfx);
	t_level.Draw(gfx);

	t_HighScore.Draw(gfx);
	highScore.Draw(gfx);
	t_Score.Draw(gfx);
	score.SetPostion(30, 80);
	score.AlignLeft();
	score.Draw(gfx);
}

void Game::Draw_Play()
{
	life.Draw(gfx);
	for (const Brick& b : bricks)
	{
		b.Draw(gfx);
	}
	ball.Draw(gfx);
	paddle.Draw(gfx);
	powerUps.Draw(gfx);

	walls.Draw(gfx);
	thinWalls.Draw(gfx);
	infoWalls.Draw(gfx);

	// draw stuff in infoWalls
	t_lvl.Draw(gfx);
	lvl.SetPostion(755, 80);
	lvl.AlignMiddle();
	lvl.Draw(gfx);

	t_HighScore.Draw(gfx);
	highScore.Draw(gfx);
	t_Score.Draw(gfx);
	score.SetPostion(30, 80);
	score.AlignLeft();
	score.Draw(gfx);
}

void Game::Draw_End()
{
	infoBorder.Draw(gfx);
	bottomBorder.Draw(gfx);
	border.Draw(gfx);

	t_Title.Draw(gfx);
	t_GameOver.Draw(gfx);
	t_DEM0N194.Draw(gfx);
	t_Thanks.Draw(gfx);

	t_PressSpace.SetText("Press Space to Continue");
	t_PressSpace.Draw(gfx);

	score.SetPostion(420, 320);
	score.AlignMiddle();
	score.Draw(gfx);

	SpriteCodex::DrawLogo(Vec2(gfx.ScreenWidth-176-30, 690), gfx);
	SpriteCodex::DrawLogo(Vec2(30, 690), gfx);
}

void Game::Draw_Win()
{
	infoBorder.Draw(gfx);
	bottomBorder.Draw(gfx);
	border.Draw(gfx);

	t_Title.Draw(gfx);
	t_YouWin.Draw(gfx);
	t_DEM0N194.Draw(gfx);
	t_Thanks.Draw(gfx);

	t_PressSpace.SetText("Press Space to Continue");
	t_PressSpace.Draw(gfx);

	score.SetPostion(420, 320);
	score.AlignMiddle();
	score.Draw(gfx);

	SpriteCodex::DrawLogo(Vec2(gfx.ScreenWidth-176-30, 690), gfx);
	SpriteCodex::DrawLogo(Vec2(30, 690), gfx);
}

void Game::LoadLevel()
{
	Brick::SetLevel(lvl.GetNum());
	switch (lvl.GetNum())
	{
		case 1:
			Lvl_01();
			break;
		case 2:
			Lvl_02();
			break;
		default:
			gameState = WIN;
			break;
	}
}

void Game::Lvl_01()
{
	const Vec2 topLeft(20.0f, 225.0f);
	const Brick::Type brickTypes[5] = {Brick::Type::SILVER, Brick::Type::RED, Brick::Type::YELLOW, Brick::Type::BLUE, Brick::Type::GREEN};
	for (int y = 0; y < nBricksDown; y++)
	{
		const Brick::Type brickType = brickTypes[y];
		for (int x = 0; x < nBricksAcross; x++)
		{
			bricks[x + y * nBricksAcross] = Brick(RectF(topLeft + Vec2(x * brickWidth, y * brickHeight), brickWidth, brickHeight), brickType);
		}
	}
}

void Game::Lvl_02()
{
	const Vec2 topLeft(20.0f, 225.0f);
	const Brick::Type brickTypes[5] = {Brick::Type::SILVER, Brick::Type::MAGENTA, Brick::Type::CYAN, Brick::Type::YELLOW, Brick::Type::GREEN};
	for (int y = 0; y < nBricksDown; y++)
	{
		const Brick::Type brickType = brickTypes[y];
		for (int x = 0; x < nBricksAcross; x++)
		{
			bricks[x + y * nBricksAcross] = Brick(RectF(topLeft + Vec2(x * brickWidth, y * brickHeight), brickWidth, brickHeight), brickType);
		}
	}
}
