#include "Snek.h"

Snek::Snek(Location& spawnLoc)
{
	Respawn(spawnLoc);
}

void Snek::Draw(Board& brd)
{
	segments[0].DrawHead(brd);
	for (int i = nSegments; i > 0; i--)
		segments[i].Draw(brd);
}

void Snek::MoveBy(Board& brd, Location& delta_location)
{
	for (int i = nSegments - 1; i > 0; i--)
		segments[i].Follow(segments[i - 1]);
	TP(brd, delta_location);
	segments[0].MoveBy(delta_location);
}

void Snek::Grow()
{
	Color col = getColor();
	segments[nSegments].InitBody(col);
	nSegments++;
}

Location Snek::GetHeadLocation()
{
	return segments[0].GetLocation();
}

Location Snek::GetHeadNextLocation(Location& delta_location)
{
	Location temp = segments[0].GetLocation();
	temp.Add(delta_location);
	return temp;
}

int Snek::GetNSegments()
{
	return nSegments;
}

bool Snek::CheckSelfCollision()
{
	for (int i = nSegments - 1; i > 0; i--)
	{
		Location loc_segment = segments[i].GetLocation();
		Location loc_head = GetHeadLocation();
		if (loc_head.x == loc_segment.x && loc_head.y == loc_segment.y)
			return true;
	}
	return false;
}

void Snek::Respawn(Location& spawnLoc)
{
	nSegments = 1;
	segments[0].InitHead(spawnLoc);
}

void Snek::TP(Board& brd, Location& delta_location)
{
//	for (int i = 0; i < nSegments; i++)
//		segments[i].TP(brd);

	segments[0].TPHead(brd, delta_location);
}

Color Snek::getColor()
{
	if (colorCounter == 1)
	{
		colorCounter++;
		return Colors::Red;
	}
	else if (colorCounter == 2)
	{
		colorCounter++;
		return Colors::MakeRGB(255, 165, 0);
	}
	else if (colorCounter == 3)
	{
		colorCounter++;
		return Colors::Yellow;
	}
	else if (colorCounter == 4)
	{
		colorCounter++;
		return Colors::Green;
	}
	else if (colorCounter == 5)
	{
		colorCounter++;
		return Colors::Blue;
	}
	else if (colorCounter == 6)
	{
		colorCounter = 1;
		return Colors::MakeRGB(75, 0, 130);
	}

	return Colors::Green;
}

void Snek::togglePrideMode()
{
	if (isPride)
	{
		colorCounter = 1;
		isPride = false;
		for (int i = 1; i < nSegments; i++)
			segments[i].InitBody(getColor());
	}
	else
	{
		colorCounter = 0;
		for (int i = 1; i < nSegments; i++)
			segments[i].InitBody(getColor());
		isPride = true;
	}
}

Location Snek::GetLocation(int x)
{
	return Location(segments[x].GetLocation());
}

bool Snek::IsInSameTile(Location& loc)
{
	for (int i = 0; i < nSegments; i++)
		if (segments[i].IsInSameTile(loc))
			return true;
	return false;
}

void Snek::Segment::Draw(Board& brd)
{
	brd.DrawCellWithOutline1(loc, c);
}

void Snek::Segment::DrawHead(Board& brd)
{
	Color c = Colors::MakeRGB(0, 170, 0);
	brd.DrawCell(loc, c);
	brd.DrawCellWithOutline4(loc, Snek::headColor);
}

void Snek::Segment::InitHead(Location in_loc)
{
	c = Snek::headColor;
	bool isHead = true;
	loc = in_loc;
}

void Snek::Segment::InitBody(Color col)
{
	c = col;
}

void Snek::Segment::Follow(const Segment& next)
{
	loc = next.loc;
}

void Snek::Segment::MoveBy(Location& delta_location)
{
	loc.Add(delta_location);
}

Location Snek::Segment::GetLocation()
{
	return loc;
}

void Snek::Segment::TPHead(Board& brd, Location& delta_location)
{
	Location temp = loc;
	temp.Add(delta_location);
	if (temp.x < 1)
		loc.x = brd.getWidth();
	else if (temp.x > brd.getWidth()-1)
		loc.x = 0;
	else if (temp.y < 1)
		loc.y = brd.getHeight();
	else if (temp.y > brd.getHeight()-1)
		loc.y = 0;
}
bool Snek::Segment::IsInSameTile(Location& in_loc)
{
	return in_loc.x == loc.x && in_loc.y == loc.y;
}
/*
void Snek::Segment::TP(Board& brd)
{
	if (loc.x < 1)
		loc.x = brd.getWidth();
	else if (loc.x > brd.getWidth() - 1)
		loc.x = 0;
	else if (loc.y < 1)
		loc.y = brd.getHeight();
	else if (loc.y > brd.getHeight() - 1)
		loc.y = 0;

}
*/