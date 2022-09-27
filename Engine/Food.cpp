#include "Food.h"

Food::Food(Board& brd, Snek& snek):
	rng(std::random_device()())
{
	Respawn(snek);
	Draw(brd);
}

void Food::Draw(Board& brd)
{
	Color c(255, 255, 255);
	brd.DrawCell(loc, c);
}

bool Food::CheckIsEaten(Snek& snek, Location& delta_location)
{
	Location in_loc = snek.GetHeadLocation();
	in_loc.Add(delta_location);
	return in_loc.x == loc.x && in_loc.y == loc.y;
}

void Food::Respawn(Snek& snek)
{
	std::uniform_int_distribution<int> locDistX(2, 37);
	std::uniform_int_distribution<int> locDistY(2, 27);
	loc = { locDistX(rng), locDistY(rng) };
	if (snek.IsInSameTile(loc))
		Respawn(snek);
}		   
