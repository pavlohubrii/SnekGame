#include "Board.h"

Board::Board(Graphics& gfx):
	gfx(gfx)
{}

void Board::DrawCell(Location & loc, Color c)
{
	gfx.DrawRectDim(loc.x * cellSize, loc.y * cellSize, cellSize, cellSize, c);
}

bool Board::IsInsideOfBoard(Location& loc)
{
	return !(loc.x < 1 || loc.x > width-1 ||
		loc.y < 1 || loc.y > height-1);
}

void Board::DrawCellWithOutline1(Location& loc, Color c)
{
	gfx.DrawRectDim(loc.x * cellSize + 1, loc.y * cellSize + 1, cellSize - 2, cellSize - 2, c);
}

void Board::DrawCellWithOutline4(Location& loc, Color c)
{
	gfx.DrawRectDim(loc.x * cellSize + 4, loc.y * cellSize + 4, cellSize - 8, cellSize - 8, c);
}

void Board::DrawBoardOutline()
{
	Color c = Colors::Red;
	for (int i = 19; i < 780; i++)
		gfx.PutPixel(i, 19, c);

	for (int i = 19; i < 780; i++)
		gfx.PutPixel(i, 579, c);

	for (int i = 19; i < 580; i++)
		gfx.PutPixel(19, i, c);

	for (int i = 19; i < 580; i++)
		gfx.PutPixel(779, i, c);
}

int Board::getWidth()
{
	return width;
}

int Board::getHeight()
{
	return height;
}
