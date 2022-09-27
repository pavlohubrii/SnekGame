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
#include "Snek.h"
#include "Food.h"
#include "Sprite.h"
#include "Sound.h"
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
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	void Pause();
	void RainbowBoost();
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	std::mt19937 rng;
	Location headLoc = {1,1};
	Location delta_location = { 1, 0 };
	Snek snek;
	Board brd;
	int snekMovePeriod = 30;
	int snekMoveCount = 0;
	bool isEaten = false;
	Food food;
	bool isGameOver = false;
	Sprite sprite;
	bool isMovingUp = false;
	bool isMovingDown = false;
	bool isMovingLeft = false;
	bool isMovingRight = false;
	void resetMoveBool();
	int superBoost = 0;
	bool boostIsActive = false;
	bool breakIsActive = false;
	bool turboBoostIsActive = false;
	bool normalSpeedIsActive = true;
	Sound eaten;
	Sound died;
	bool deadSoundPlayed = false;
	bool colorChange = false;
	bool isOnPause = false;
	bool escIsPressed = false;
	int i = 0;
	/********************************/
};