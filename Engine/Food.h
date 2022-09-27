#pragma once
#include "Board.h"
#include "Snek.h"
#include <random>

class Food
{
	Location loc;
	std::mt19937 rng;
public:
	Food(Board& brd, Snek& snek);
	void Draw(Board& brd);
	bool CheckIsEaten(Snek& snek, Location &delta);
	void Respawn(Snek& snek);
};

