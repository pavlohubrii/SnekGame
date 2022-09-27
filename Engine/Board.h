#pragma once
#include "Location.h"
#include "Graphics.h"

class Board
{
private:
	static constexpr int width = 39;
	static constexpr int height = 29;
	static constexpr int cellSize = 20;

	Graphics& gfx;
public:
	Board(Graphics& gfx);
	void DrawCell(Location& loc, Color c);
	bool IsInsideOfBoard(Location& loc);
	void DrawCellWithOutline1(Location& loc, Color c);
	void DrawCellWithOutline4(Location& loc, Color c);
	void DrawBoardOutline();
	int getWidth();
	int getHeight();
};

