#include "Location.h"

void Location::Add(const Location& input_loc)
{
	x = input_loc.x + x;
	y = input_loc.y + y;
}
