/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Sound.h"
#include "FrameTimer.h"
#include "Text.h"
#include "Counter.h"

#include "Ball.h"
#include "Brick.h"
#include "Paddle.h"
#include "Walls.h"
#include "LifeCounter.h"
#include "Border.h"
#include "PowerUps.h"
#include "Laser.h"

#include <random>

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel(float dt);
	/********************************/
	/*  User Functions              */
	/********************************/
	void Game_Start(float dt);
	void Game_Ready(float dt);
	void Game_Play(float dt);
	void Game_EndWin(float dt);
	void Game_Pause(float dt);

	void Draw_Start();
	void Draw_Ready();
	void Draw_Play();
	void Draw_End();
	void Draw_Win();
	void Draw_Pause();

	void InitializeText();
	void ResetGame();
	void LoadLevel();

	void Lvl_01();
	void Lvl_02();
private:
	enum class GameStates
	{
		START,
		READY,
		PLAY,
		END,
		WIN,
		PAUSE
	};
private:
	MainWindow& wnd;
	Graphics gfx;
	FrameTimer ft;
	/********************************/
	/*  User Variables              */
	/********************************/
	std::mt19937 rng;
	std::uniform_int_distribution<int> rxDist;
	int ballRelativeX;

	GameStates gameState;
	bool spacePressed = false;
	bool escapePressed = false;
	bool countDownStarted = false;

	static constexpr float brickWidth = 60.0f;
	static constexpr float brickHeight = 25.0f;
	static constexpr int nBricksAcross = 13;
	static constexpr int nBricksDown = 5;
	static constexpr int nBricks = nBricksAcross * nBricksDown;
	Brick bricks[nBricks];

	static constexpr float wallThickness = 20.0f;
	static constexpr int fieldHeight = 750;
	Walls walls;
	Walls thinWalls;
	Walls infoWalls;
	Border infoBorder;
	Border bottomBorder;
	Border border;

	Ball ball;
	Paddle paddle;
	LifeCounter life;
	PowerUps powerUps;
	Laser laser;
	
	Counter lvl;
	Counter highScore;
	Counter score;
	Counter countDown;

	static constexpr float readyWaitTime = 2.0f;
	float currentWaitTime = 0.0f;

	PowerUps::PowerUpIcon p_Laser;
	PowerUps::PowerUpIcon p_Expand;
	PowerUps::PowerUpIcon p_Catch;
	PowerUps::PowerUpIcon p_Slow;
	PowerUps::PowerUpIcon p_Triple;
	PowerUps::PowerUpIcon p_Vaus;

	Text t_Laser;	Text t_L;
	Text t_Expand;	Text t_E;
	Text t_Catch;	Text t_C;
	Text t_Slow;	Text t_S;
	Text t_Triple;	Text t_T;
	Text t_Vaus;	Text t_V;

	Text t_Title;
	Text t_GameOver;
	Text t_YouWin;
	Text t_DEM0N194;
	Text t_level;
	Text t_lvl;
	Text t_Ready;
	Text t_HighScore;
	Text t_Score;
	Text t_PressSpace;
	Text t_PowerUps;
	Text t_P;
	Text t_Thanks;
	Text t_Pause;
};