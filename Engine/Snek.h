#pragma once
#include "Board.h"

class Snek
{
private:
	class Segment
	{
	private:
		Location loc;
		Color c;
		bool isHead;
	public:
		void Draw(Board& brd);
		void DrawHead(Board& brd);
		void InitHead(Location in_loc);
		void InitBody(Color col);
		void Follow(const Segment& next);
		void MoveBy(Location& delta_location);
		Location GetLocation();
		void TPHead(Board& brd, Location& delta_location);
		bool IsInSameTile(Location& in_loc);
	};

private:
	static constexpr int nSegmentsMax = 1000;
	int nSegments = 1;
	static constexpr Color headColor = Colors::Green;
	static constexpr Color bodyColor = Colors::Green;
	Segment segments[nSegmentsMax];
	int colorCounter = 0;
public:
	Snek(Location& spawnLoc);
	void Draw(Board& brd);
	void MoveBy(Board& brd, Location& delta_location);
	void Grow();
	Location GetHeadLocation();
	Location GetHeadNextLocation(Location& delta_location);
	int GetNSegments();
	bool CheckSelfCollision();
	void Respawn(Location& spawnLoc);
	void TP(Board& brd, Location& delta_location);
	Color getColor();
	bool isPride = true;
	void togglePrideMode();
	Location GetLocation(int x);
	bool IsInSameTile(Location& loc);
};

