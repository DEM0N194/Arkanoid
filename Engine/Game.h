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
	void Game_End(float dt);

	void Draw_Start();
	void Draw_Game();
	void Draw_End();

	void InitializeText();
private:
	enum eGameStates
	{
		START,
		READY,
		PLAY,
		END
	};
private:
	MainWindow& wnd;
	Graphics gfx;
	FrameTimer ft;
	/********************************/
	/*  User Variables              */
	/********************************/
	eGameStates gameState;
	bool spacePressed = false;

	static constexpr float brickWidth = 60.0f;
	static constexpr float brickHeight = 25.0f;
	static constexpr int nBricksAcross = 13;
	static constexpr int nBricksDown = 4;
	static constexpr int nBricks = nBricksAcross * nBricksDown;
	Brick bricks[nBricks];

	static constexpr float wallThickness = 20.0f;
	static constexpr int fieldHeight = 750;
	Walls walls;
	Border infoBorder;
	Border border;

	Ball ball;
	Paddle paddle;
	LifeCounter life;
private:
	Text t_Title;
	Text t_GameOver;
};