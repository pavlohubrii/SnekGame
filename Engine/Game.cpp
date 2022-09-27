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

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	rng(std::random_device()()),
	brd(gfx),
	snek(headLoc),
	food(brd, snek),
	eaten(L"eaten.wav"),
	died(L"died.wav")
{
	std::uniform_int_distribution<int> locXDist(3, 36);
	std::uniform_int_distribution<int> locYDist(3, 26);
	Location loc = { locXDist(rng), locYDist(rng) };
	snek.Respawn(loc);
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
	if (wnd.kbd.KeyIsPressed(VK_ESCAPE) && !escIsPressed)
	{
		Pause();
		escIsPressed = true;
	}
	else if (!wnd.kbd.KeyIsPressed(VK_ESCAPE))
		escIsPressed = false;


	if(!isOnPause)
	{
		if(!isGameOver)
		{
			if ((wnd.kbd.KeyIsPressed(VK_UP) || wnd.kbd.KeyIsPressed('W')) && !isMovingDown)
			{
				delta_location = { 0, -1 };
				resetMoveBool();
				isMovingUp = true;
			}
			else if ((wnd.kbd.KeyIsPressed(VK_DOWN) || wnd.kbd.KeyIsPressed('S')) && !isMovingUp)
			{
				delta_location = { 0, 1 };
				resetMoveBool();
				isMovingDown = true;
			}
			else if ((wnd.kbd.KeyIsPressed(VK_LEFT) || wnd.kbd.KeyIsPressed('A')) && !isMovingRight)
			{
				delta_location = { -1, 0 };
				resetMoveBool();
				isMovingLeft = true;
			}
			else if ((wnd.kbd.KeyIsPressed(VK_RIGHT) || wnd.kbd.KeyIsPressed('D')) && !isMovingLeft)
			{
				delta_location = { 1, 0 };
				resetMoveBool();
				isMovingRight = true;
			}

			boostIsActive = wnd.kbd.KeyIsPressed(VK_SHIFT);
			breakIsActive = wnd.kbd.KeyIsPressed(VK_CONTROL);
			turboBoostIsActive = wnd.kbd.KeyIsPressed(VK_SPACE);

			if (boostIsActive)
			{
				snekMovePeriod = 15;
				normalSpeedIsActive = false;
			}
			else if (breakIsActive)
			{
				snekMovePeriod = 60;
				normalSpeedIsActive = false;
			}
			else if (turboBoostIsActive && superBoost > 0)
			{
				snekMovePeriod = 5;
				superBoost--;
				normalSpeedIsActive = false;
			}
			else
			{
				snekMovePeriod = 30;
				normalSpeedIsActive = true;
			}

			isGameOver = /*!brd.IsInsideOfBoard(snek.GetHeadNextLocation(delta_location)) || */snek.CheckSelfCollision();
			if (snekMoveCount >= snekMovePeriod)
			{	
				isEaten = food.CheckIsEaten(snek, delta_location);
				//if (wnd.kbd.KeyIsPressed('G'))
				//	snek.Grow();

				if (isEaten)
				{
					snek.Grow();
					food.Respawn(snek);
					isEaten = false;
					superBoost = 100;
					eaten.Play();
					//				snekMovePeriod--;
					//				snekMovePeriodStored--;
				}
				//			snek.TP(brd, delta_location);
				snek.MoveBy(brd, delta_location);
				snekMoveCount = 0;
			}

			snekMoveCount++;
		}



		if (wnd.kbd.KeyIsPressed('R') && isGameOver)
		{
			std::uniform_int_distribution<int> locXDist(1, 39);
			std::uniform_int_distribution<int> locYDist(1, 29);
			Location spawnLoc = { locXDist(rng), locYDist(rng) };
			snek.Respawn(spawnLoc);
			isGameOver = false;
			delta_location = { 1, 0 };
			food.Respawn(snek);
			snekMovePeriod = 30;
			superBoost = 0;
			deadSoundPlayed = false;
		}

		if (wnd.kbd.KeyIsPressed('P') && !colorChange)
		{
			snek.togglePrideMode();
			colorChange = true;
		}
		else if (!wnd.kbd.KeyIsPressed('P'))
			colorChange = false;

		if (!deadSoundPlayed && isGameOver)
		{
			died.Play();
			deadSoundPlayed = true;
		}
	}
}

void Game::Pause()
{
	if (isOnPause)
		isOnPause = false;
	else
		isOnPause = true;
}

void Game::RainbowBoost()
{
	if (i < 10)
	{
		gfx.DrawRectDim(0, 580, 800, 19, Colors::MakeRGB(255, 0, 0));
		i++;
	}
	else if (i < 20)
	{
		gfx.DrawRectDim(0, 580, 800, 19, Colors::MakeRGB(255, 165, 0));
		i++;
	}
	else if (i < 30)
	{
		gfx.DrawRectDim(0, 580, 800, 19, Colors::MakeRGB(255, 255, 0));
		i++;
	}
	else if (i < 40)
	{
		gfx.DrawRectDim(0, 580, 800, 19, Colors::MakeRGB(0, 255, 0));
		i++;
	}
	else if (i < 50)
	{
		gfx.DrawRectDim(0, 580, 800, 19, Colors::MakeRGB(0, 255, 255));
		i++;
	}
	else if (i < 60)
	{
		gfx.DrawRectDim(0, 580, 800, 19, Colors::MakeRGB(0, 0, 255));
		i++;
	}
	else if (i < 70)
	{
		gfx.DrawRectDim(0, 580, 800, 19, Colors::MakeRGB(255, 255, 0));
		i++;
	}
	else if (i >= 70)
		i = 0;

}

void Game::resetMoveBool()
{
	isMovingDown = false;
	isMovingUp = false;
	isMovingLeft = false;
	isMovingRight = false;
}

void Game::ComposeFrame()
{
	snek.Draw(brd);
	food.Draw(brd);
	if (isGameOver)
	{
		sprite.DrawGameOver(gfx);
	}
	brd.DrawBoardOutline();
	gfx.DrawRectDim(0, 0, superBoost*8, 19, Colors::Blue); 

	if (boostIsActive)
		gfx.DrawRectDim(0, 580, 800, 19, Colors::Green);
	else if (breakIsActive)
		gfx.DrawRectDim(0, 580, 800, 19, Colors::Red);
	else if (turboBoostIsActive && superBoost > 0)
		RainbowBoost();
	else
		gfx.DrawRectDim(0, 580, 800, 19, Colors::Yellow);
}
