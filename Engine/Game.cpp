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
//TODO:		Laser		-Red		- done
//TODO:		Enlarge		-Blue		- done
//TODO:		Catch		-Green		- done
//TODO:		Slow		-Orange		- done
//TODO:		Disruption	-Cyan		- done
//TODO:		Vaus		-Grey		- done
//TODO:		Break		-Magenta	- done

//TODO: add more Levels

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	rng(std::random_device()()),
	rxDist(10, 45),
	// Walls and borders
	walls(RectF(wallThickness, float(gfx.ScreenWidth)-wallThickness, float(gfx.ScreenHeight-fieldHeight), float(gfx.ScreenHeight)), int(wallThickness)),
	thinWalls(RectF(10, float(gfx.ScreenWidth)-10, float(gfx.ScreenHeight-fieldHeight)-10, float(gfx.ScreenHeight)), 10),
	infoWalls(RectF(10, float(gfx.ScreenWidth)-10, 10, float(gfx.ScreenHeight-fieldHeight)-10), int(10)),
	border(RectF(wallThickness, float(gfx.ScreenWidth)-wallThickness, wallThickness, float(gfx.ScreenHeight)-wallThickness), int(wallThickness)),
	infoBorder(RectF(10, float(gfx.ScreenWidth)-10, 10, float(gfx.ScreenHeight-fieldHeight)-wallThickness), 10),
	bottomBorder(RectF(10, float(gfx.ScreenWidth)-10, 680, float(gfx.ScreenHeight)-10), 10),
	gameState(GameStates::START),
	powerUps(paddle, life),
	laser(paddle, walls),
	// power ups on the title screen
	p_Laser(Vec2(140,280),PowerUps::Type::LASER),
	p_Expand(Vec2(450,280), PowerUps::Type::ENLARGE),
	p_Catch(Vec2(140,360), PowerUps::Type::CATCH),
	p_Slow(Vec2(450,360), PowerUps::Type::SLOW),
	p_Triple(Vec2(140,440), PowerUps::Type::DISRUPTION),
	p_Vaus(Vec2(450,440), PowerUps::Type::VAUS),
	// sounds
	s_Bottom(L"Sounds/Bottom.mp3"),
	s_Ending(L"Sounds/Ending.mp3"),
	s_Game_Over(L"Sounds/Game_Over.mp3"),
	s_Paddle(L"Sounds/Paddle.mp3"),
	s_Switch(L"Sounds/Switch.mp3"),
	s_Title_Screen(L"Sounds/Title_Screen.mp3"),
	s_Round_Start(L"Sounds/Round_Start.mp3")
{
	border.SetColor(Color(130, 130, 130));
	infoBorder.SetColor(Color(130, 130, 130));
	bottomBorder.SetColor(Color(130, 130, 130));
	lvl.SetNumOf0(1);
	lvl_s.SetNumOf0(1);
	lvl_s.SetPostion(550+3, 500+3);
	lvl_s.AlignRight();
	lvl_s.SetColor(Color(0, 0, 0));
	highScore.SetPostion(440, 80);
	highScore.AlignMiddle();
	countDown.SetPostion(400, 580);

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
	t_YouWin.SetColor(Colors::Green);
	t_PressSpace.SetPostion(0, 550);
	t_PressSpace.AlignMiddle();
	t_DEM0N194.SetText("DEM0N194");
	t_DEM0N194.SetPostion(0, 760);
	t_DEM0N194.AlignMiddle();
	t_DEM0N194.SetColor(150, 150, 150);
	t_level.SetText("LEVEL");
	t_level.SetPostion(305, 500);
	t_level_s.SetText("LEVEL");
	t_level_s.SetPostion(305+3, 500+3);
	t_level_s.SetColor(Color(0, 0, 0));
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
	t_Pause.SetText("PAUSED...");
	t_Pause.SetPostion(0, 500);
	t_Pause.AlignMiddle();
	t_Pause_s.SetText("PAUSED...");
	t_Pause_s.SetPostion(0+3, 500+3);
	t_Pause_s.AlignMiddle();
	t_Pause_s.SetColor(Color(0, 0, 0));
}

void Game::ResetGame()
{
	Ball::ResetSpeed();
	balls.clear();
	balls.push_back(Ball());
	paddle = Paddle(Vec2(410, 810), 60, 10);
	life = LifeCounter(Vec2(30, 880), 3);
	powerUps.DestroyAll();

	lvl = 1;
	lvl_s = 1;
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
		case GameStates::START:
			Game_Start(dt);
			break;
		case GameStates::READY:
			Game_Ready(dt);
			break;
		case GameStates::PLAY:
			Game_Play(dt);
			break;
		case GameStates::END:
			Game_EndWin(dt);
			break;
		case GameStates::WIN:
			Game_EndWin(dt);
			break;
		case GameStates::PAUSE:
			Game_Pause(dt);
	}
}

void Game::ComposeFrame()
{
	switch (gameState)
	{
		case GameStates::START:
			Draw_Start();
			break;
		case GameStates::READY:
			Draw_Ready();
			break;
		case GameStates::PLAY:
			Draw_Play();
			break;
		case GameStates::END:
			if (currentWaitTime < 1.0f)
			{
				Draw_Play();
			}
			else
			{
				Draw_End();
			}
			break;
		case GameStates::WIN:
			if (currentWaitTime < 1.0f)
			{
				Draw_Play();
			}
			else
			{
				Draw_Win();
			}
			break;
		case GameStates::PAUSE:
			Draw_Pause();
			break;
	}
}

void Game::Game_Start(float dt)
{
	if (wnd.kbd.KeyIsPressed(VK_SPACE))
	{
		if (!spacePressed)
		{
			s_Title_Screen.StopOne();
			s_Ending.StopOne();
			s_Round_Start.Play();
			gameState = GameStates::READY;
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
	powerUps.Update(int(gameState), dt);

	if (paddle.LaserActive())
	{
		laser.Update(dt);
		for (unsigned int i = 0; i < bricks.size(); i++)
		{
			bricks[i].ExecuteLaserCollision(laser);
		}
	}

	// the ball sticks to the paddle
	balls.at(0) = Ball(paddle.GetRect().GetCenter() + Vec2(float(ballRelativeX),-17),paddle.GetBallDir(balls.at(0)), walls.GetColor(), walls.GetColor());

	currentWaitTime += dt;
	if (currentWaitTime > readyWaitTime)
	{
		currentWaitTime = 0.0f;
		gameState = GameStates::PLAY;
	}
	else if (currentWaitTime > readyWaitTime/2)
	{
		powerUps.DisableCurrent();
		paddle.Restore();
	}
}

void Game::Game_Play(float dt)
{
	if (PowerUps::TripleActive() && !PowerUps::TripleInited())
	{
		balls.push_back(Ball(balls.at(0), 0.2f));
		balls.push_back(Ball(balls.at(0), -0.2f));
		PowerUps::TripleInit();
	}

	paddle.Update(wnd.kbd, dt);
	paddle.DoWallCollision(walls.GetInnerBounds());
	powerUps.Update(int(gameState), dt);

	laser.Update(dt);

	if (paddle.Catched())
	{
		balls.at(0) = Ball(paddle.GetRect().GetCenter() + Vec2(float(ballRelativeX), -17),paddle.GetBallDir(balls.at(0)),
						   balls.at(0).GetColor(), balls.at(0).GetColorGoal());
	}
	else
	{
		for (auto& b : balls)
		{
			b.Update(dt);
		}
	}

	bool levelCleared = true;
	bool ball2brickCollisionHappened = false;
	float curColDistSq;
	int curColIndex;
	int curBallIndex = -1;
	for (unsigned int i = 0; i < bricks.size(); i++)
	{
		// collision of the ball with the bricks
		for (unsigned int j = 0; j < balls.size(); j++)
		{
			if (bricks[i].CheckBallCollision(balls.at(j)))
			{
				const float newColDistSq = (balls.at(j).GetPosition() - bricks[i].GetCenter()).GetLengthSq();
				if (ball2brickCollisionHappened)
				{
					if (newColDistSq < curColDistSq)
					{
						curColDistSq = newColDistSq;
						curColIndex = i;
						curBallIndex = j;
					}
				}
				else
				{
					curColDistSq = newColDistSq;
					curColIndex = i;
					curBallIndex = j;
					ball2brickCollisionHappened = true;
				}
				break;
			}
		}
		
		if (paddle.LaserActive())
		{
			bricks[i].ExecuteLaserCollision(laser);
		}

		// if any of the bricks is not destroyed, the level is not cleared
		if (bricks[i].IsDestroyed() == false)
		{
			levelCleared = false;
		}
	}
	if (ball2brickCollisionHappened)
	{
		balls.at(curBallIndex).ResetCoolDown();
			// returns true if the brick is destroyed
		if (bricks[curColIndex].ExecuteBallCollision(balls.at(curBallIndex)))
		{
			powerUps.Gimme(bricks[curColIndex].GetCenter());
			if (!PowerUps::TripleActive() && bricks[curColIndex].GetValue() != 0)
			{
				Ball::SpeedUp();
			}
			// track scores
			score += bricks[curColIndex].GetValue();
			highScore = std::max(highScore.GetNum(), score.GetNum());
		}
	}

	// collision of the ball with the paddle
	for (unsigned int j = 0; j < balls.size(); j++)
	{
		if (paddle.DoBallCollision(balls.at(j)))
		{
			if (paddle.CatchActive())
			{
				paddle.CatchBall();
				ballRelativeX = int(balls.at(j).GetRect().GetCenter().x - paddle.GetRect().GetCenter().x);
			}
			s_Paddle.Play();
		}
	}
	
	// collision of the ball with the wall is handled here
	for (unsigned int j = 0; j < balls.size(); j++)
	{
		const Ball::Collision ball2wallCollsion = balls.at(j).DoWallCollisions(walls.GetInnerBounds());
		if (ball2wallCollsion == Ball::Collision::SIDE_TOP)
		{
			if (!paddle.GetRect().IsOverlappingWith(balls.at(j).GetRect()))
			{
				balls.at(j).ResetCoolDown();
			}
		}
		else if (ball2wallCollsion == Ball::Collision::BOTTOM)
		{
			s_Bottom.Play();
			if (balls.size() == 1)
			{
				// true if you consume your last life
				if(life.ConsumeLife())
				{
					gameState = GameStates::END;
					s_Game_Over.Play();
				}
				else
				{
					gameState = GameStates::READY;
					paddle.Destroy();
					Ball::ResetSpeed();
					ballRelativeX = rxDist(rng);
					s_Round_Start.Play();
				}
			}
			else
			{
				balls.erase(balls.begin() + j);
				if (balls.size() == 1)
				{
					PowerUps::DisableTriple();
				}
			}
		}
	}

	if (wnd.kbd.KeyIsPressed(VK_SPACE))
	{
		if (!spacePressed)
		{
			///PowerUps::ActivateTriple();
			///balls.push_back(Ball(balls.at(0), 0.2f));
			///levelCleared = true;
			///powerUps.Gimme(Vec2(500, 300));

			if (paddle.Catched())
			{
				paddle.ReleaseBall();
			}
			if (paddle.LaserActive())
			{
				laser.Shoot();
			}
			spacePressed = true;
		}
	}
	else
	{
		spacePressed = false;
	}

	if (wnd.kbd.KeyIsPressed(VK_ESCAPE))
	{
		if (!escapePressed)
		{
			s_Switch.Play();
			gameState = GameStates::PAUSE;
			escapePressed = true;
		}
	}
	else
	{
		escapePressed = false;
	}

	//! LEVEL CLEARED
	if (levelCleared || paddle.GoToNextLvl())
	{
		if (paddle.GoToNextLvl())
		{
			score += 10000;
			highScore = std::max(highScore.GetNum(), score.GetNum());
		}
		gameState = GameStates::READY;
		paddle.Destroy();
		laser.DestroyLeft();
		laser.DestroyRight();
		Ball::ResetSpeed();
		lvl++;
		lvl_s++;
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
				s_Switch.Play();
				gameState = GameStates::START;
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

void Game::Game_Pause(float dt)
{
	if (wnd.kbd.KeyIsPressed(VK_ESCAPE))
	{
		if (!escapePressed)
		{
			countDownStarted = true;
			escapePressed = true;
		}
	}
	else
	{
		escapePressed = false;
	}

	if (countDownStarted)
	{
		currentWaitTime += dt;

		if (currentWaitTime < 0.5f)
		{
			countDown = 3;
		}
		else if (currentWaitTime < 1.0f)
		{
			countDown = 2;
		}
		else if (currentWaitTime < 1.5f)
		{
			countDown = 1;
		}
		else
		{
			currentWaitTime = 0.0f;
			countDownStarted = false;
			gameState = GameStates::PLAY;
		}

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
	walls.Draw(gfx);
	thinWalls.Draw(gfx);
	infoWalls.Draw(gfx);

	life.Draw(gfx);
	if (currentWaitTime > readyWaitTime/2)
	{
		for (Ball& b : balls)
		{
			b.Draw(gfx);
		}
		t_Ready.Draw(gfx);
	}
	paddle.breakOut.Draw(gfx);
	paddle.Draw(gfx);
	powerUps.Draw(gfx);
	for (const Brick& b : bricks)
	{
		b.Draw(gfx);
	}

	if (paddle.LaserActive())
	{
		laser.Draw(gfx);
	}
	
	// draw lvl in the infoWalls
	lvl.SetPostion(755, 80);
	lvl.AlignMiddle();
	lvl.Draw(gfx);
	t_lvl.Draw(gfx);
	// draw lvl in the middle of the screen
	lvl.SetPostion(550, 500);
	lvl.AlignRight();
	lvl_s.Draw(gfx);
	lvl.Draw(gfx);
	t_level_s.Draw(gfx);
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
	walls.Draw(gfx);
	thinWalls.Draw(gfx);
	infoWalls.Draw(gfx);

	life.Draw(gfx);
	for (const Brick& b : bricks)
	{
		b.Draw(gfx);
	}
	for (Ball& b : balls)
	{
		b.Draw(gfx);
	}
	paddle.breakOut.Draw(gfx);
	paddle.Draw(gfx);
	powerUps.Draw(gfx);

	if (paddle.LaserActive())
	{
		laser.Draw(gfx);
	}

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

void Game::Draw_Pause()
{
	Draw_Play();
	t_Pause_s.Draw(gfx);
	t_Pause.Draw(gfx);
	if (currentWaitTime != 0.0f)
	{
		countDown.Draw(gfx);
	}
}

void Game::LoadLevel()
{
	s_Round_Start.Play();
	bricks.clear();
	Brick::SetLevel(lvl.GetNum());
	switch (lvl.GetNum())
	{
		case 1:
			Lvl_01();
			break;
		case 2:
			Lvl_02();
			break;
		case 3:
			Lvl_03();
			break;
		case 4:
			Lvl_04();
			break;
		default:
			gameState = GameStates::WIN;
			s_Round_Start.StopOne();
			s_Ending.Play();
			break;
	}
}

void Game::Lvl_01()
{
	walls.SetColor(Color(0, 75, 150));
	thinWalls.SetColor(Color(0, 75, 150));
	infoWalls.SetColor(Color(0, 75, 150));
	const Vec2 topLeft(20.0f, 225.0f);
	const Brick::Type brickTypes[5] = {Brick::Type::SILVER, Brick::Type::RED, Brick::Type::YELLOW, Brick::Type::BLUE, Brick::Type::GREEN};
	for (int y = 0; y < 5; y++)
	{
		const Brick::Type brickType = brickTypes[y];
		for (int x = 0; x < 13; x++)
		{
			bricks.push_back(Brick(RectF(topLeft + Vec2(x * brickWidth, y * brickHeight), brickWidth, brickHeight), brickType));
		}
	}
}

void Game::Lvl_02()
{
	walls.SetColor(Color(50, 150, 50));
	thinWalls.SetColor(Color(50, 150, 50));
	infoWalls.SetColor(Color(50, 150, 50));
	const Vec2 topLeft(20.0f, 200.0f);
	const Brick::Type brickTypes[8] = {Brick::Type::WHITE, Brick::Type::ORANGE, Brick::Type::CYAN, Brick::Type::GREEN,
									   Brick::Type::RED, Brick::Type::BLUE, Brick::Type::MAGENTA, Brick::Type::YELLOW};
	int yMin = 0;
	for (int x = 0; x < 12; x++)
	{
		const Brick::Type brickType = brickTypes[x%8];
		for (int y = 11; y >= yMin; y--)
		{
			bricks.push_back(Brick(RectF(topLeft + Vec2(x * brickWidth, y * brickHeight), brickWidth, brickHeight), brickType));
		}
		yMin++;

		bricks.push_back(Brick(RectF(topLeft + Vec2(x * brickWidth, 12 * brickHeight), brickWidth, brickHeight), Brick::Type::SILVER));
	}
	bricks.push_back(Brick(RectF(topLeft + Vec2(12 * brickWidth, 12 * brickHeight), brickWidth, brickHeight), brickTypes[4]));
}

void Game::Lvl_03()
{
	walls.SetColor(Color(150, 50, 50));
	thinWalls.SetColor(Color(150, 50, 50));
	infoWalls.SetColor(Color(150, 50, 50));
	const Vec2 topLeft(20.0f, 225.0f);
	const Brick::Type brickTypes[8] = {Brick::Type::WHITE, Brick::Type::ORANGE, Brick::Type::CYAN, Brick::Type::GREEN,
		Brick::Type::RED, Brick::Type::BLUE, Brick::Type::MAGENTA, Brick::Type::YELLOW};

	for (int y = 0; y < 14; y++)
	{
		for (int x = 0; x < 13; x++)
		{
			if (x != 0 && x != 6 && x != 12)
			{
				const Brick::Type brickType = brickTypes[(y+x)%8];
				bricks.push_back(Brick(RectF(topLeft + Vec2(x * brickWidth, y * brickHeight), brickWidth, brickHeight), brickType));
			}
		}
	}
}

void Game::Lvl_04()
{
	walls.SetColor(Color(50, 100, 150));
	thinWalls.SetColor(Color(50, 100, 150));
	infoWalls.SetColor(Color(50, 100, 150));
	const Vec2 topLeft(20.0f, 200.0f);
	const Brick::Type brickTypes[8] = {Brick::Type::GREEN, Brick::Type::WHITE, Brick::Type::RED, Brick::Type::WHITE,
		Brick::Type::MAGENTA, Brick::Type::BLUE, Brick::Type::CYAN, Brick::Type::CYAN};

	Brick::Type type;
	for (int y = 0; y < 15; y += 2)
	{
		for (int x = 0; x < 13; x++)
		{
			if (y == 14)
			{
				if (x < 10)
				{
					type = Brick::Type::GOLD;
				}
				else 
				{
					type = brickTypes[y/2];
				}
			}
			else if(y == 10)
			{
				if (x >= 3)
				{
					type = Brick::Type::GOLD;
				}
				else
				{
					type = brickTypes[y/2];
				}
			}
			else if (y == 6)
			{
				if (x < 10)
				{
					type = Brick::Type::GOLD;
				}
				else
				{
					type = brickTypes[y/2];
				}
			}
			else if (y == 2)
			{
				if (x >= 3)
				{
					type = Brick::Type::GOLD;
				}
				else
				{
					type = brickTypes[y/2];
				}
			}
			else
			{
				type = brickTypes[y/2];
			}
			bricks.push_back(Brick(RectF(topLeft + Vec2(x * brickWidth, y * brickHeight), brickWidth, brickHeight), type));
		}
	}
}
